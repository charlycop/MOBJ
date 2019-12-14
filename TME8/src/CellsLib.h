// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELLSLIB_H
#define NETLIST_CELLSLIB_H

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
#include "CellsModel.h"
//#include "CellViewer.h"

class QPainter;



namespace Netlist {

class CellViewer;

class CellsLib : public QWidget {
    Q_OBJECT;
  public:
                       CellsLib       ( QWidget* parent=NULL );
    inline void        setCellViewer  ( CellViewer* );
           int         getSelectedRow () const;
    inline CellsModel* getBaseModel   ();
  public slots:
           void        load           ();
  private:
    CellViewer*  cellViewer_;
    CellsModel*  baseModel_;
    QTableView*  view_;
    QPushButton* load_;
};

inline CellsModel* CellsLib::getBaseModel   ()              { return baseModel_; }
inline void        CellsLib::setCellViewer  (CellViewer* c) { cellViewer_ = c;   }

}  // Netlist namespace.

#endif  // NETLIST_CELLSLIB_H