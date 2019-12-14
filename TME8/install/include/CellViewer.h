#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  <QMenuBar>
#include  <QMainWindow>

#include  "SaveCellDialog.h"
#include  "OpenCellDialog.h"
#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"
//#include  "InstancesWidget.h"
//#include "CellsLib.h"




namespace Netlist{
class InstancesWidget;
class CellsLib;

    class CellViewer : public QMainWindow {
        Q_OBJECT;
      public:
                          CellViewer          ( QWidget* parent=NULL );
        virtual          ~CellViewer          ();
        inline  Cell*     getCell             () const;
     //   inline  CellsLib* getCellsLib         ();  // TME9+.
      public slots:
                void      setCell             ( Cell* );
                void      saveCell            ();
                void      openCell            ();
                void      showCellsLib        ();  // TME9+.
                void      showInstancesWidget ();  // TME9+.
      private:
        CellWidget*      cellWidget_;
        CellsLib*        cellsLib_;         // TME9+.
        InstancesWidget* instancesWidget_;  // TME9+.
        SaveCellDialog*  saveCellDialog_;
        OpenCellDialog*  openCellDialog_;
    };

    inline Cell* CellViewer::getCell             () const{ return cellWidget_->getCell(); }

} // Fin de Netlist


#endif  // NETLIST_CELL_VIEWER_H