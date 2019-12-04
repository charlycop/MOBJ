// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_OPEN_CELL_DIALOG_H
#define NETLIST_OPEN_CELL_DIALOG_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QDialog>
#include  <QLineEdit>

class QPainter;
#include "Box.h"


namespace Netlist {

  class  OpenCellDialog : public  QDialog {
      Q_OBJECT;
    public:
      OpenCellDialog ( QWidget* parent=NULL );
      bool              run               ( std::string* );
      const  QString    getCellName     ()  const;
      void              setCellName     ( const  QString& );
    protected:
      QLineEdit*      lineEdit_;
  };


}  // Netlist namespace.

#endif  // NETLIST_OPEN_CELL_DIALOG_H