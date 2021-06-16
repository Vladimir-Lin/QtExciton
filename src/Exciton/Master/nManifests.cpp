#include <exciton.h>

#define Decide decisions[GuiNativeId]

///////////////////////////////////////////////////////////////////////////
//                  Decision tables for Manifests                        //
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////

N::Manifests:: Manifests  (ManifestTypes mType,QWidget * parent,Plan * p)
             : TreeWidget (                              parent,       p)
             , Object     (0,Types::None                                )
             , CheckType  (mType                                        )
             , Sorting    (Qt::DescendingOrder                          )
{
  Configure ( ) ;
}

N::Manifests::~Manifests (void)
{
}

void N::Manifests::InstallDecisions(void)
{
}

bool N::Manifests::acceptTap(QTapGesture * gesture)
{
  if ( IsNull(gesture) ) return false      ;
  QTreeWidgetItem * item = currentItem ( ) ;
  if (NotNull(item)) CheckButtons ( )      ;
  return false                             ;
}

bool N::Manifests::acceptTapHold(QTapAndHoldGesture * gesture)
{
  if ( IsNull(gesture) ) return false        ;
  QTreeWidgetItem * item = currentItem ( )   ;
  if (NotNull(item))                         {
    int column = currentColumn()             ;
    allowGesture = false                     ;
    emit itemDoubleClicked ( item , column ) ;
    return true                              ;
  }                                          ;
  return false                               ;
}

bool N::Manifests::acceptPan(QPanGesture * gesture)
{
  return false ;
}

bool N::Manifests::acceptPinch(QPinchGesture * gesture)
{
  return false ;
}

bool N::Manifests::acceptSwipe(QSwipeGesture * gesture)
{
  if ( IsNull(gesture) ) return false      ;
  if ( gesture->horizontalDirection()!=QSwipeGesture::Right ||
       gesture->verticalDirection  ()!=QSwipeGesture::NoDirection) return false ;
  QTreeWidgetItem * item = currentItem ( ) ;
  if (NotNull(item))                       {
    switch (CheckType)                     {
      case Inventory                       :
        DeleteInventory ( )                ;
      break                                ;
      case CheckItem                       :
        Delete          ( )                ;
      break                                ;
    }                                      ;
    return true                            ;
  }                                        ;
  return false                             ;
}

void N::Manifests::mousePressEvent(QMouseEvent * event)
{
  QPoint            ps   = event->pos (    )                ;
  QTreeWidgetItem * it   = itemAt     ( ps )                ;
  bool              pass = false                            ;
  if (!IsMask(event->buttons(),Qt::LeftButton)) pass = true ;
  if (NotNull(it)                             ) pass = true ;
  if (NotNull(ItemEditing)                    ) pass = true ;
  if (!allowGesture                           ) pass = true ;
  if (pass)                                                 {
    if (NotNull(ItemEditing))                               {
      event->accept()                                       ;
    } else                                                  {
      TreeWidget::mousePressEvent(event)                    ;
    }                                                       ;
  } else                                                    {
    allowGesture = false                                    ;
    event->accept()                                         ;
    switch (CheckType)                                      {
      case Inventory                                        :
        InsertInventory ( )                                 ;
      break                                                 ;
      case CheckItem                                        :
        Insert          ( )                                 ;
      break                                                 ;
    }                                                       ;
  }                                                         ;
}

void N::Manifests::Configure(void)
{
  NewTreeWidgetItem       ( head  )                       ;
  switch (CheckType)                                      {
    case Inventory                                        :
      head->setText(0,tr("Inventory"))                    ;
      head->setTextAlignment(0,Qt::AlignCenter)           ;
    break                                                 ;
    case CheckItem                                        :
      head->setText(0,tr("Item"))                         ;
      head->setTextAlignment(0,Qt::AlignCenter)           ;
    break                                                 ;
  }                                                       ;
  setColumnCount               ( 1                      ) ;
  setRootIsDecorated           ( false                  ) ;
  setAlternatingRowColors      ( true                   ) ;
  setFont                      ( head , Fonts::ListView ) ;
  setHeaderItem                ( head                   ) ;
  setDragDropMode              ( NoDragDrop             ) ;
  plan->setFont                ( this                   ) ;
  MountClicked                 ( 2                      ) ;
  grabGesture                  ( Qt::TapGesture         ) ;
  grabGesture                  ( Qt::TapAndHoldGesture  ) ;
  grabGesture                  ( Qt::PanGesture         ) ;
  grabGesture                  ( Qt::PinchGesture       ) ;
  grabGesture                  ( Qt::SwipeGesture       ) ;
  allowGesture = true                                     ;
}

bool N::Manifests::FocusIn(void)
{
  switch (CheckType)                       {
    case Inventory                         :
      LinkAction(Play,Go               ()) ;
      LinkAction(Insert,InsertInventory()) ;
      LinkAction(Delete,DeleteInventory()) ;
      LinkAction(Rename,RenameInventory()) ;
    break                                  ;
    case CheckItem                         :
      LinkAction(Insert,Insert         ()) ;
      LinkAction(Delete,Delete         ()) ;
      LinkAction(Rename,Rename         ()) ;
    break                                  ;
  }                                        ;
  CheckButtons ( )                         ;
  return true                              ;
}

bool N::Manifests::FocusOut(void)
{
  return false ;
}

bool N::Manifests::startup(void)
{
  clear           ( ) ;
  CheckButtons    ( ) ;
  switch (CheckType)  {
    case Inventory    :
      start ( 10001 ) ;
    break             ;
    case CheckItem    :
      start ( 10002 ) ;
    break             ;
  }                   ;
  return true         ;
}

bool N::Manifests::startup(QString name,SUID u)
{
  QTreeWidgetItem * head = headerItem() ;
  uuid = u                              ;
  clear           (          )          ;
  CheckButtons    (          )          ;
  head->setText   ( 0 , name )          ;
  switch (CheckType)                    {
    case Inventory                      :
      start ( 10001 )                   ;
    break                               ;
    case CheckItem                      :
      start ( 10002 )                   ;
    break                               ;
  }                                     ;
  return true                           ;
}

void N::Manifests::run(int Type,ThreadData * data)
{ Q_UNUSED ( data )      ;
  switch (Type)          {
    case 10001           :
      CheckInventory ( ) ;
      ListInventory  ( ) ;
    break                ;
    case 10002           :
      VerifyItems    ( ) ;
      ListItems      ( ) ;
    break                ;
  }                      ;
  CheckButtons       ( ) ;
}

void N::Manifests::CheckButtons(void)
{
  QTreeWidgetItem * it = currentItem()      ;
  QAction         * aa                      ;
  switch (CheckType)                        {
    case Inventory                          :
      if (IsNull(it))                       {
        aa = plan->Action(N::Menus::Play  ) ;
        aa-> setEnabled  (false           ) ;
        aa = plan->Action(N::Menus::Delete) ;
        aa-> setEnabled  (false           ) ;
        aa = plan->Action(N::Menus::Rename) ;
        aa-> setEnabled  (false           ) ;
      } else                                {
        aa = plan->Action(N::Menus::Play  ) ;
        aa-> setEnabled  (true            ) ;
        aa = plan->Action(N::Menus::Delete) ;
        aa-> setEnabled  (true            ) ;
        aa = plan->Action(N::Menus::Rename) ;
        aa-> setEnabled  (true            ) ;
      }                                     ;
    break                                   ;
    case CheckItem                          :
      if (IsNull(it))                       {
        aa = plan->Action(N::Menus::Delete) ;
        aa-> setEnabled  (false           ) ;
        aa = plan->Action(N::Menus::Rename) ;
        aa-> setEnabled  (false           ) ;
      } else                                {
        aa = plan->Action(N::Menus::Delete) ;
        aa-> setEnabled  (true            ) ;
        aa = plan->Action(N::Menus::Rename) ;
        aa-> setEnabled  (true            ) ;
      }                                     ;
    break                                   ;
  }                                         ;
}

QString N::Manifests::CreateManifest(QString table)
{
  QString T                                          ;
  if (Book.isSQLITE())                               {
    T  = Book.CreateTable(table)                     ;
    T += " ("                                        ;
    T += "id integer primary key autoincrement,"     ;
    T += "uuid bigint unsigned not null,"            ;
    T += "name blob not null,"                       ;
    T += "ltime timestamp default CURRENT_TIMESTAMP" ;
    T += ") ;"                                       ;
  } else
  if (Book.isMySQL())                                {
    T  = Book.CreateTable(table)                     ;
    T += " ("                                        ;
    T += "id integer primary key auto_increment,"    ;
    T += "uuid bigint unsigned not null,"            ;
    T += "name blob not null,"                       ;
    T += "ltime timestamp default CURRENT_TIMESTAMP"
         " on update CURRENT_TIMESTAMP"              ;
    T += ") "                                        ;
    T += Book.Options                                ;
    T += ";"                                         ;
  }                                                  ;
  return T                                           ;
}

void N::Manifests::CheckInventory(void)
{
  if (Book.isSQLITE())                                   {
    QFileInfo F(Book.dbName)                             ;
    if (!F.exists())                                     {
      Settings s                                         ;
      s . Mode     = "SQL"                               ;
      s . SQL      = new N::Sql()                        ;
      (*(s.SQL))   = Book                                ;
      s . Table    = "settings"                          ;
      s . Username = plan->Hostname                      ;
      s . Initialize ( )                                 ;
    }                                                    ;
  }                                                      ;
  SqlConnection SC(Book)                                 ;
  if (SC.open("Manifests"))                              {
    QStringList       T = SC.Tables()                    ;
    QString           Q                                  ;
    QTreeWidgetItem * it                                 ;
    bool        success = false                          ;
    if (!T.contains(Book.TableName))                     {
      if (Book.isSQLITE())                               {
        Q  = Book.CreateTable(Book.TableName)            ;
        Q += " ("                                        ;
        Q += "id integer primary key autoincrement,"     ;
        Q += "uuid bigint unsigned not null,"            ;
        Q += "name blob not null,"                       ;
        Q += "type integer default 0,"                   ;
        Q += "item blob not null,"                       ;
        Q += "icon longblob,"                            ;
        Q += "ltime timestamp default CURRENT_TIMESTAMP" ;
        Q += ") ;"                                       ;
      } else
      if (Book.isMySQL())                                {
        Q  = Book.CreateTable(Book.TableName)            ;
        Q += " ("                                        ;
        Q += "id integer primary key auto_increment,"    ;
        Q += "uuid bigint unsigned not null,"            ;
        Q += "name blob not null,"                       ;
        Q += "type integer default 0,"                   ;
        Q += "item blob not null,"                       ;
        Q += "icon longblob,"                            ;
        Q += "ltime timestamp default CURRENT_TIMESTAMP"
             " on update CURRENT_TIMESTAMP"              ;
        Q += ") "                                        ;
        Q += Book.Options                                ;
        Q += ";"                                         ;
      }                                                  ;
      if (SC.Query(Q))                                   {
        success = true                                   ;
      } else                                             {
        Q = SC.q.lastError().text()                      ;
        it = new QTreeWidgetItem ( )                     ;
        it->setText(0,tr("Error - %1").arg(Q))           ;
        addTopLevelItem(it)                              ;
      }                                                  ;
    } else success = true                                ;
    SC.close()                                           ;
    setEnabled(success)                                  ;
  } else                                                 {
    NewTreeWidgetItem(it)                                ;
    it->setText(0,tr("Database seems disabled"))         ;
    addTopLevelItem(it)                                  ;
    setEnabled(false)                                    ;
  }                                                      ;
  SC.remove()                                            ;
}

void N::Manifests::ListInventory(void)
{
  SqlConnection SC(Book)            ;
  if (SC.open("Manifests"))         {
    QString Q                       ;
    Q = Book.SelectFrom             (
          "uuid,name"               ,
          Book.TableName            ,
          SC.OrderBy("id",Sorting)) ;
    SqlLoopNow ( SC , Q )           ;
      SUID    u = SC.Uuid  (0)      ;
      QString n = SC.String(1)      ;
      NewTreeWidgetItem(it)         ;
      it->setData(0,Qt::UserRole,u) ;
      it->setText(0,n             ) ;
      addTopLevelItem(it)           ;
    SqlLoopErr ( SC , Q )           ;
    SqlLoopEnd ( SC , Q )           ;
    SC.close()                      ;
  }                                 ;
  SC.remove()                       ;
}

void N::Manifests::VerifyItems(void)
{
  SqlConnection SC(Book)                                 ;
  if (SC.open("Manifests"))                              {
    bool    success = false                              ;
    QString Q                                            ;
    Q = Book.SelectFrom                                  (
          "item"                                         ,
          Book.TableName                                 ,
          SC.WhereUuid(uuid)                           ) ;
    if (SC.Fetch(Q)) Book.ExtraAttributes = SC.String(0) ;
    SC.close()                                           ;
    success = ( Book.ExtraAttributes.length() > 0 )      ;
    setEnabled(success)                                  ;
  } else                                                 {
    NewTreeWidgetItem(it)                                ;
    it->setText(0,tr("Database seems disabled"))         ;
    addTopLevelItem(it)                                  ;
    setEnabled(false)                                    ;
  }                                                      ;
  SC.remove()                                            ;
}

void N::Manifests::ListItems(void)
{
  SqlConnection SC(Book)            ;
  if (SC.open("Manifests"))         {
    QString Q                       ;
    Q = Book.SelectFrom             (
          "uuid,name"               ,
          Book.ExtraAttributes      ,
          SC.OrderBy("id",Sorting)) ;
    SqlLoopNow ( SC , Q )           ;
      SUID    u = SC.Uuid  (0)      ;
      QString n = SC.String(1)      ;
      NewTreeWidgetItem(it)         ;
      it->setData(0,Qt::UserRole,u) ;
      it->setText(0,n             ) ;
      addTopLevelItem(it)           ;
    SqlLoopErr ( SC , Q )           ;
    SqlLoopEnd ( SC , Q )           ;
    SC.close()                      ;
  }                                 ;
  SC.remove()                       ;
}

void N::Manifests::GainFocus(void)
{
  FocusIn ( ) ;
}

void N::Manifests::Go(void)
{
  QTreeWidgetItem * item = currentItem()  ;
  if (IsNull(item)) return                ;
  SUID u = nTreeUuid ( item , 0 )         ;
  if ( u <= 0 ) return                    ;
  emit Edit(this,item->text(0),u)         ;
}

void N::Manifests::InsertInventory(void)
{
  NewTreeWidgetItem(item)                        ;
  item->setData(0,Qt::UserRole,0)                ;
  if (nEqual(Sorting,Qt::AscendingOrder))        {
    addTopLevelItem(item)                        ;
  } else                                         {
    insertTopLevelItem(0,item)                   ;
  }                                              ;
  doubleClicked(item,0)                          ;
  plan->showMessage(tr("Insert a new manifest")) ;
}

void N::Manifests::DeleteInventory(void)
{
  QTreeWidgetItem * item = currentItem()     ;
  if (IsNull(item)) return                   ;
  SUID u = nTreeUuid ( item , 0 )            ;
  QString n = item->text(0)                  ;
  takeItem(item)                             ;
  if ( u <= 0 ) return                       ;
  SqlConnection SC(Book)                     ;
  if (SC.open("DeleteInventory"))            {
    QString Q                                ;
    QString T                                ;
    Q = Book.SelectFrom                      (
          "item"                             ,
          Book.TableName                     ,
          SC.WhereUuid(u)                  ) ;
    if (SC.Fetch(Q)) T = SC.String(0)        ;
    Q = Book.DeleteFrom                      (
          Book.TableName                     ,
          SC.WhereUuid(u)                  ) ;
    SC.Query(Q)                              ;
    Q = QString("drop table %1 ;").arg(T)    ;
    SC.Query(Q)                              ;
    SC.close()                               ;
  }                                          ;
  SC.remove()                                ;
  plan->showMessage(tr("%1 deleted").arg(n)) ;
}

void N::Manifests::RenameInventory(void)
{
  QTreeWidgetItem * item = currentItem() ;
  if (IsNull(item)) return               ;
  doubleClicked ( item , 0 )             ;
}

void N::Manifests::Insert(void)
{
  NewTreeWidgetItem(item)                 ;
  item->setData(0,Qt::UserRole,0)         ;
  if (nEqual(Sorting,Qt::AscendingOrder)) {
    addTopLevelItem(item)                 ;
  } else                                  {
    insertTopLevelItem(0,item)            ;
  }                                       ;
  doubleClicked(item,0)                   ;
}

void N::Manifests::Delete(void)
{
  QTreeWidgetItem * item = currentItem()     ;
  if (IsNull(item)) return                   ;
  SUID u = nTreeUuid ( item , 0 )            ;
  QString n = item->text(0)                  ;
  takeItem(item)                             ;
  if ( u <= 0 ) return                       ;
  SqlConnection SC(Book)                     ;
  if (SC.open("Delete"))                     {
    QString Q                                ;
    Q = Book.DeleteFrom                      (
          Book.ExtraAttributes               ,
          SC.WhereUuid(u)                  ) ;
    SC.Query(Q)                              ;
    SC.close()                               ;
  }                                          ;
  SC.remove()                                ;
  plan->showMessage(tr("%1 deleted").arg(n)) ;
}

void N::Manifests::Rename(void)
{
  QTreeWidgetItem * item = currentItem() ;
  if (IsNull(item)) return               ;
  doubleClicked ( item , 0 )             ;
}

void N::Manifests::doubleClicked(QTreeWidgetItem * item,int column)
{
  QLineEdit * line                             ;
  QAction   * aa                               ;
  allowGesture = false                         ;
  switch (column)                              {
    case 0                                     :
      aa = plan->Action(N::Menus::Insert)      ;
      if (NotNull(aa)) aa->setEnabled(false)   ;
      switch (CheckType)                       {
        case Inventory                         :
          line = setLineEdit                   (
                   item,column                 ,
                   SIGNAL(editingFinished())   ,
                   SLOT  (nameFinished   ()) ) ;
        break                                  ;
        case CheckItem                         :
          line = setLineEdit                   (
                   item,column                 ,
                   SIGNAL(editingFinished())   ,
                   SLOT  (itemFinished   ()) ) ;
        break                                  ;
      }                                        ;
      line->setFocus ( Qt::TabFocusReason )    ;
    break                                      ;
  }                                            ;
}

void N::Manifests::nameFinished(void)
{
  QAction * aa = plan->Action(N::Menus::Insert)        ;
  if (NotNull(aa)) aa->setEnabled(true)                ;
  nDropOut ( IsNull(ItemEditing) )                     ;
  QLineEdit * line = Casting(QLineEdit,ItemWidget)     ;
  nDropOut ( IsNull(line       ) )                     ;
  SUID    u    = nTreeUuid(ItemEditing,0)              ;
  QString name = line->text()                          ;
  EnterSQL ( SC , Book )                               ;
    QString Q                                          ;
    if ( u == 0 )                                      {
      if (name.length()>0)                             {
        QString T                                      ;
        u = SC.Unique(Book.TableName,"uuid")           ;
        T = QString("L%1").arg(u)                      ;
        Q = Book.InsertInto                            (
              Book.TableName                           ,
              3                                        ,
              "uuid"                                   ,
              "name"                                   ,
              "item"                                 ) ;
        SC . Prepare ( Q                             ) ;
        SC . Bind    ( "uuid" , u                    ) ;
        SC . Bind    ( "name" , name.toUtf8()        ) ;
        SC . Bind    ( "item" , T   .toUtf8()        ) ;
        SC . Exec    (                               ) ;
        Q  = CreateManifest ( T                      ) ;
        SC . Query   ( Q                             ) ;
        ItemEditing->setData( 0 , Qt::UserRole, u    ) ;
        ItemEditing->setText( 0 , name               ) ;
      }                                                ;
    } else                                             {
      Q = Book.Update                                  (
            Book.TableName                             ,
            SC.WhereUuid(uuid)                         ,
            1                                          ,
            "name"                                   ) ;
      SC . Prepare ( Q                               ) ;
      SC . Bind    ( "uuid" , u                      ) ;
      SC . Bind    ( "name" , name.toUtf8()          ) ;
      SC . Exec    (                                 ) ;
      ItemEditing->setText( 0 , name )                 ;
    }                                                  ;
  LeaveSQL ( SC , Book )                               ;
  removeOldItem ( true , 0 )                           ;
  Alert         ( Done     )                           ;
  allowGesture = true                                  ;
}

void N::Manifests::itemFinished(void)
{
  QAction * aa = plan->Action(N::Menus::Insert)        ;
  if (NotNull(aa)) aa->setEnabled(true)                ;
  nDropOut ( IsNull(ItemEditing) )                     ;
  QLineEdit * line = Casting(QLineEdit,ItemWidget)     ;
  nDropOut ( IsNull(line       ) )                     ;
  SUID    u    = nTreeUuid(ItemEditing,0)              ;
  QString name = line->text()                          ;
  EnterSQL ( SC , Book )                               ;
    QString Q                                          ;
    if ( u == 0 )                                      {
      if (name.length()>0)                             {
        u = SC.Unique(Book.ExtraAttributes,"uuid")     ;
        Q = Book.InsertInto                            (
              Book.ExtraAttributes                     ,
              2                                        ,
              "uuid"                                   ,
              "name"                                 ) ;
        SC . Prepare ( Q                             ) ;
        SC . Bind    ( "uuid" , u                    ) ;
        SC . Bind    ( "name" , name.toUtf8()        ) ;
        SC . Exec    (                               ) ;
        ItemEditing->setData( 0 , Qt::UserRole, u    ) ;
        ItemEditing->setText( 0 , name               ) ;
      }                                                ;
    } else                                             {
      Q = Book.Update                                  (
            Book.ExtraAttributes                       ,
            SC.WhereUuid(uuid)                         ,
            1                                          ,
            "name"                                   ) ;
      SC . Prepare ( Q                               ) ;
      SC . Bind    ( "uuid" , u                      ) ;
      SC . Bind    ( "name" , name.toUtf8()          ) ;
      SC . Exec    (                                 ) ;
      ItemEditing->setText( 0 , name )                 ;
    }                                                  ;
  LeaveSQL ( SC , Book )                               ;
  removeOldItem ( true , 0 )                           ;
  Alert         ( Done     )                           ;
  allowGesture = true                                  ;
}
