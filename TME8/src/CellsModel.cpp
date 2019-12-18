#include  <QMainWindow>
#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  <QLabel>
#include  <QLineEdit>
#include  <QPushButton>
#include  <QHBoxLayout>
#include  <QMenuBar>

#include  <QVBoxLayout>
#include  <QAbstractTableModel>
#include  "CellsModel.h"
#include  "Instance.h"
#include  "Cell.h"
#include  <string>

namespace Netlist{

    CellsModel :: CellsModel ( QObject* parent )
    : QAbstractTableModel(parent)
    , cell_(NULL)
    { 
    }

    //void CellsModel::cellLoaded(){}

    CellsModel ::~CellsModel  ()
    { }

    void CellsModel::updateDatas(){
        emit  layoutChanged ();
    }
    

    int   CellsModel :: rowCount(const  QModelIndex& parent) const{

        return Cell::getAllCells().size();
    }

    int   CellsModel :: columnCount(const  QModelIndex& parent) const{ 
        return  1; 
    }

    QVariant   CellsModel::data( const  QModelIndex& index, int  role ) const{
        std::cout << "On entre ici" << std::endl;
        if (not  index.isValid ())  return  QVariant ();
       // std::cout << "------\nROLE : " << role << "(" <<Qt:: DisplayRole<<")"<< std::endl;

        if (role == Qt::DisplayRole) {
            int  row = index.row();
         //   std::cout << "------\nROLE : " << role << "(" <<Qt::DisplayRole<<")"<< std::endl;
            return  cell_->getAllCells()[row]->getName().c_str();            
        }

        if(role == Qt::TextAlignmentRole){
            return Qt::AlignCenter;
        }


        return  QVariant ();
    }

    QVariant   CellsModel :: headerData( int   section, Qt:: Orientation  orientation, int   role ) const{
        if (orientation  == Qt:: Vertical) return  QVariant ();
        if (role != Qt:: DisplayRole) return  QVariant ();
        switch ( section ) {
            case 0:  return "MasterCells";
        }
        return  QVariant ();
    }

    Cell* CellsModel :: getModel ( int row ){
        //if (not  cell_) return  NULL;
        if (row  >= (int)Cell::getAllCells().size())  return  NULL;
        return  Cell::getAllCells()[row];
    }

    



} // Fin namespace Netlist