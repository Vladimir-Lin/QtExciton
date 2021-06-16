#include <exciton.h>
#include "ui_XcityOrganization.h"

N::XcityOrganization:: XcityOrganization ( QWidget * parent , Plan * p )
                     : Widget            (           parent ,        p )
                     , ui                ( new Ui::XcityOrganization   )
                     , groups            ( NULL                        )
{
  ui -> setupUi ( this ) ;
}

N::XcityOrganization::~XcityOrganization(void)
{
  delete ui ;
}

SUID N::XcityOrganization::CompanyUuid(void)
{
  if (IsNull(groups)) return 0 ;
  return groups->toUuid()      ;
}

QString N::XcityOrganization::Search(void)
{
  return ui->XcityJpComId->text() ;
}

QString N::XcityOrganization::CompanySpot(void)
{
  return ui->XcityJpComMark->text() ;
}

void N::XcityOrganization::prepare(void)
{
  groups  = new ComboBox ( this , plan           )   ;
  groups -> setGeometry  (  20 , 140 , 440 ,  28 )   ;
  groups -> setEditable  ( true                  )   ;
  ////////////////////////////////////////////////////
  nConnect ( groups , SIGNAL ( activated    (int))   ,
             this   , SLOT   ( GroupChanged (int)) ) ;
  ////////////////////////////////////////////////////
  plan -> setFont ( this )                           ;
}

void N::XcityOrganization::configure(QString scope,Sql & sql)
{
  QString       CN = QtUUID::createUuidString()             ;
  /////////////////////////////////////////////////////////
  SqlConnection SC ( plan -> sql )                        ;
  GroupItems    GI ( plan        )                        ;
  if (SC.open("Initialize",CN))                           {
    UUIDs   Uuids                                         ;
    ///////////////////////////////////////////////////////
    Uuids = GI . Groups                                   (
              SC                                          ,
              Types::Organization                         ,
              SC.OrderByAsc("id")                       ) ;
    ///////////////////////////////////////////////////////
    groups -> blockSignals ( true       )                 ;
    groups -> addItems     ( SC , Uuids )                 ;
    groups -> blockSignals ( false      )                 ;
    ///////////////////////////////////////////////////////
    SC.close()                                            ;
  }                                                       ;
  SC.remove()                                             ;
  /////////////////////////////////////////////////////////
  plan -> site . beginGroup ( scope                     ) ;
  if (plan->site.contains("XcityJpComSkip"))              {
    bool skip                                             ;
    skip = plan->site.value("XcityJpComSkip").toBool()    ;
    ui  -> XcityJpSkip      -> blockSignals ( true  )     ;
    ui  -> XcityJpSkip      -> setChecked   ( skip  )     ;
    ui  -> XcityJpSkip      -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpComId"))                {
    QString xcity                                         ;
    xcity = plan->site.valueString("XcityJpComId")        ;
    ui -> XcityJpComId      -> blockSignals ( true  )     ;
    ui -> XcityJpComId      -> setText      ( xcity )     ;
    ui -> XcityJpComId      -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityJpComMark"))              {
    QString xcity                                         ;
    xcity = plan->site.valueString("XcityJpComMark")      ;
    ui -> XcityJpComMark    -> blockSignals ( true  )     ;
    ui -> XcityJpComMark    -> setText      ( xcity )     ;
    ui -> XcityJpComMark    -> blockSignals ( false )     ;
  }                                                       ;
  if (plan->site.contains("XcityCompany"))                {
    SUID suid                                             ;
    suid = plan->site.value("XcityCompany").toULongLong() ;
    *groups <= suid                                       ;
    DoProcessEvents                                       ;
  }                                                       ;
  plan -> site . endGroup   (                           ) ;
  /////////////////////////////////////////////////////////
  hunterSql = sql                                         ;
  Scope     = scope                                       ;
}

void N::XcityOrganization::GroupChanged(int index)
{ Q_UNUSED                ( index              ) ;
  SUID u = groups->toUuid (                    ) ;
  nDropOut                ( u <= 0             ) ;
  plan->site.beginGroup   ( Scope              ) ;
  plan->site.setValue     ( "XcityCompany" , u ) ;
  plan->site.endGroup     (                    ) ;
}

void N::XcityOrganization::XcityJpChanged(void)
{
  QString path                                                                 ;
  bool    skip    = ui -> XcityJpSkip      -> isChecked ( )                    ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.beginGroup                ( Scope                               ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.setValue                  ( "XcityJpComSkip"    , skip          ) ;
  //////////////////////////////////////////////////////////////////////////////
  path = ui->XcityJpComId      -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpComId"      , path.toUtf8() ) ;
  path = ui->XcityJpComMark    -> text (                                     ) ;
  plan->site.setValue                  ( "XcityJpComMark"    , path.toUtf8() ) ;
  //////////////////////////////////////////////////////////////////////////////
  plan->site.endGroup                  (                                     ) ;
}

void N::XcityOrganization::XcityValueChanged(int)
{
  XcityJpChanged ( ) ;
}
