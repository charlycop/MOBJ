// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"


namespace Netlist {

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



  CellWidget::CellWidget ( QWidget* parent )
    : QWidget(parent)
    , cell_  (NULL)
    , viewport_(Box (0 ,0 ,500 ,500))
  {
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    setAttribute    ( Qt::WA_StaticContents );
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }


  CellWidget::~CellWidget ()
  { }


  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint();
  }


  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }


  void  CellWidget::resizeEvent ( QResizeEvent* event ){
    const  QSize& size = event ->size ();
    //  Assume  the  resize  is  always  done by  drawing  the  bottom  right  corner.
    viewport_.setX2( viewport_.getX1() + size.width  () );
    viewport_.setY1( viewport_.getY2() - size.height () );
    cerr  << "CellWidget :: resizeEvent ()␣viewport_:" << viewport_  << endl;
}


  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    QPainter  painter(this);
    painter.setBackground( QBrush( Qt:: black ) );
    painter.eraseRect     ( QRect( QPoint (0,0), size() ) );
    painter.setPen( QPen( Qt::darkGreen , 1 ) );
    QRect  rect = boxToScreenRect(viewport_);
    painter.drawRect( rect  );
    painter.setPen   ( QPen   ( Qt::red , 0 ) );
    painter.setBrush( QBrush( Qt::red ) );
    query(1, painter);
    // ...
    //painter.drawRect( rect2  );
  }

  void   CellWidget :: keyPressEvent(QKeyEvent* event) {
    event ->ignore ();
    if (event ->modifiers () & (Qt:: ControlModifier|Qt:: ShiftModifier ))
    return;
    switch( event ->key()) {
      case Qt:: Key_Up:   goUp    ();  break;
      case Qt:: Key_Down: goDown  ();  break;
      case Qt:: Key_Left: goLeft  ();  break;
      case Qt:: Key_Right:goRight ();  break;
      default: return;
    }
    event ->accept ();
  }

  void   CellWidget :: goRight () {
    viewport_.translate( Point (-20,0) );
    repaint ();
  }

    void   CellWidget :: goLeft() {
    viewport_.translate( Point (20,0) );
    repaint ();
  }
  
  void   CellWidget ::goUp() {
    viewport_.translate( Point (0 ,-20) );
    repaint ();
  }

  void    CellWidget::goDown(){
    viewport_.translate( Point (0 ,20) );
    repaint ();
  }

  void   CellWidget ::query(unsigned  int flags , QPainter& painter) {
    if ((not  cell_) or (not  flags ))  {
     std::cout<< "HOLALA pas de CELL !" << std::endl;
       return;
    }
    const  vector <Instance*>& instances = cell_->getInstances ();

    for (size_t i=0; i<instances.size() ; ++i) {
             std::cout<< "On entre dans le for" << std::endl;
             std::cout<< "i=" << i << std::endl;
        Point           instPos = instances[i]->getPosition ();
        std::cerr << instances[i]->getName() << " (" << instPos.getX() << ","<< instPos.getY() <<")"<< std::endl;
        const  Symbol* symbol   = instances[i]->getMasterCell()->getSymbol ();

        if (not  symbol) continue;
      if (flags /*& InstanceShapes*/) {
        const  vector <Shape*>& shapes=symbol->getShapes ();

        for (size_t j=0 ; j< shapes.size() ; ++j) {
          std::cerr << "ICI" << std::endl;
          //BoxShape* boxShape = dynamic_cast <BoxShape*>(shapes[j]);
          LineShape* boxShape = dynamic_cast <LineShape*>(shapes[j]);
          if (boxShape) {
            Box    box   = boxShape ->getBoundingBox ();
            QRect  rect = boxToScreenRect(box.translate(instPos ));
            painter.drawRect(rect);
          }
        }
      }
    }
  }

}  // Netlist namespace.
