// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_SAVE_CELL_DIALOG_H
#define NETLIST_SAVE_CELL_DIALOG_H

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

  class  SaveCellDialog : public  QDialog {
      Q_OBJECT;
    public:
      SaveCellDialog ( QWidget* parent=NULL );
      bool              run               ( QString& name );
      const  QString    getCellName     ()  const;
      void              setCellName     ( const  QString& );
    protected:
      QLineEdit*      lineEdit_;
  };


}  // Netlist namespace.

#endif  // NETLIST_SAVE_CELL_DIALOG_H