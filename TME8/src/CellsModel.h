// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELLSMODEL_H
#define NETLIST_CELLSMODEL_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QDialog>
#include <QLineEdit>
#include <QAbstractTableModel>
#include "Box.h"
#include "Cell.h"

class QPainter;



namespace Netlist {

  class  CellsModel : public  QAbstractTableModel {
    Q_OBJECT;
  public :
                  CellsModel  ( QObject* parent=NULL );
                 ~CellsModel  ();
      void        setCell         ( Cell* );
      Cell*       getModel        ( int  row );
      int         rowCount        ( const  QModelIndex& parent=QModelIndex () ) const;
      int         columnCount     ( const  QModelIndex& parent=QModelIndex () ) const;
      QVariant    data            ( const  QModelIndex& index , int  role=Qt:: DisplayRole ) const;
      QVariant    headerData      ( int  section, Qt:: Orientation  orientation, int  role=Qt:: DisplayRole ) const;
      void        updateDatas     (const  QModelIndex& parent);

  private:
    Cell* cell_;
};


}  // Netlist namespace.

#endif  // NETLIST_CELLSMODEL_H