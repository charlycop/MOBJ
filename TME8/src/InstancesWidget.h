// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_INSTANCESWIDGET_H
#define NETLIST_INSTANCESWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QDialog>
#include <QLineEdit>
#include <QAbstractTableModel>
#include <QTableView>
#include "Box.h"
#include "CellViewer.h"
#include "InstancesModel.h"

class QPainter;



namespace Netlist {

class  InstancesWidget : public  QWidget {
    Q_OBJECT;
  
  public:
                        InstancesWidget   ( QWidget* parent=NULL );
  inline  void          setCellViewer     ( CellViewer* );
          int           getSelectedRow    ()  const;
  inline  void          setCell           ( Cell* );
          bool          run               ();
  
  public  slots:
          void          load              ();
  
  private:
      CellViewer*      cellViewer_;
      InstancesModel*  baseModel_;
      QTableView*      view_;
      QPushButton*     load_;
};
  
inline void InstancesWidget::setCellViewer (CellViewer* c) { cellViewer_ = c; }
inline void InstancesWidget::setCell       (Cell*       c) { baseModel_->setCell(c);}

}  // Netlist namespace.

#endif  // NETLIST_INSTANCESWIDGET_H