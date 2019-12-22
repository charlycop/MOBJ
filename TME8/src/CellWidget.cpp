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
    //setAttribute    ( Qt::WA_OpaquePaintEvent );
    //setAttribute    ( Qt::WA_NoSystemBackground );
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

    //Pour tous les nets de la cell
    for(auto& net : cell_->getNets()){
      
        // Pour toues les lines du net courant
        for(auto& line : net->getLines()){
            Point sourcePosition = line->getSourcePosition();
            Point targetPosition = line->getTargetPosition();
            painter.setPen( QPen( Qt::darkGreen , 3 ) );
            painter.drawLine(xToScreenX(sourcePosition.getX()), yToScreenY(sourcePosition.getY()), xToScreenX(targetPosition.getX()), yToScreenY(targetPosition.getY()));
        }

        // Pour tous les nodes du net courant
        for(auto& node : net->getNodes()){
            if(node == nullptr || !node->getNet()) continue;
            Point nodePosition = node->getPosition();
            std::cout  << "Node(" << node->getNet() << ")" << std::endl;

            int x = nodePosition.getX();
            int y = nodePosition.getY();

            Box    box(x-2, y-2, x+2, y+2);
            QRect  rect = boxToScreenRect(box);
            
            painter.setPen( QPen( Qt::blue ) );
            painter.setBrush(Qt::blue);
            painter.drawRect(rect);
        }
    }

    
    const  vector <Instance*>& instances = cell_->getInstances ();
    if (instances.size()){
      
      //Pour tous les terms de la cell
      for(auto& term : cell_->getTerms()){
        Point termPosition = term->getNode()->getPosition();
        int x = termPosition.getX();
        int y = termPosition.getY();

        Box    box(x-5, y-5, x+5, y+5);
        QRect  rect = boxToScreenRect(box);
        painter.setBrush(Qt::NoBrush);
        painter.setPen( QPen( Qt::yellow, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
        painter.setBrush(Qt::yellow);
        painter.drawPoint(pointToScreenPoint(term->getPosition()));
      }
  
      for (size_t i=0; i<instances.size() ; ++i) {

        Point instPos = instances[i]->getPosition ();
        const  Symbol* symbol   = instances[i]->getMasterCell()->getSymbol();

        if (not symbol) continue;
        if (flags) {
          const  vector <Shape*>& shapes=symbol->getShapes ();

          for (size_t j=0 ; j< shapes.size() ; ++j) {
            
            TermShape* termShape = dynamic_cast <TermShape*>(shapes[j]);
            if (termShape) {
              Box    box   = termShape->getBoundingBox ();
              QRect  rect = boxToScreenRect(box.translate(instPos));
              painter.drawText(rect, termShape->getAlign(), tr((termShape->getTerm()->getName()).c_str()));
              painter.setPen( QPen( Qt::red, 10/*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/) ); 
              painter.drawPoint(rect.center());
              continue;
            }

            ArcShape* arcShape = dynamic_cast <ArcShape*>(shapes[j]);
            if (arcShape) {
              Box    box   = arcShape ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box.translate(instPos));
              painter.setBrush(Qt::NoBrush);
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawArc(rect, arcShape->getStart()*16 , arcShape->getSpan()*16 );   
              continue;
            }

            LineShape* lineShape = dynamic_cast <LineShape*>(shapes[j]);
            if (lineShape) {
              Box    box   = lineShape ->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box.translate(instPos));
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawLine(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
              continue;
            }

            EllipseShape* ellipse = dynamic_cast <EllipseShape*>(shapes[j]);
            if (ellipse) {
              Box    box   = ellipse ->getBoundingBox ();
              painter.setBrush(Qt::NoBrush);
              QRect  rect = boxToScreenRect(box.translate(instPos));
              painter.drawEllipse(QRectF(rect));
              continue;
            }

            BoxShape* boxshape = dynamic_cast <BoxShape*>(shapes[j]);
            if (boxshape) {
              Box    box   = boxshape->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box.translate(instPos));
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.setBrush(Qt::NoBrush);
              painter.drawRect(rect);
              painter.drawText(rect, Qt::AlignTop|Qt::AlignLeft, tr("QtProject"));
              continue;
            }
          }
        }
      }
    }
    else{ // SI on a pas d'instances, on affiche les symboles de la cell_

        const  Symbol* symbol   = cell_->getSymbol ();
        for (auto& shape : symbol->getShapes()) {

            LineShape* lineShape = dynamic_cast <LineShape*>(shape);
            if (lineShape) {
              Box    box   = lineShape ->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box);
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawLine(rect.x(), rect.y(), rect.x()+rect.width(), rect.y()+rect.height());
              continue;
            }

            ArcShape* arcShape = dynamic_cast <ArcShape*>(shape);
            if (arcShape) {
              Box    box   = arcShape ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box);
              painter.setBrush(Qt::NoBrush);
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawArc(rect, arcShape->getStart()*16 , arcShape->getSpan()*16 );   
              continue;
            }

            EllipseShape* ellipse = dynamic_cast <EllipseShape*>(shape);
            if (ellipse) {
              Box    box   = ellipse ->getBoundingBox ();
              painter.setBrush(Qt::NoBrush);
              QRect  rect = boxToScreenRect(box);
              painter.drawEllipse(QRectF(rect));
              continue;
            }

            BoxShape* boxshape = dynamic_cast <BoxShape*>(shape);
            if (boxshape) {
              Box    box   = boxshape->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box);
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.setBrush(Qt::NoBrush);
              painter.drawRect(rect);

              continue;
            }

            TermShape* termShape = dynamic_cast <TermShape*>(shape);
            if (termShape) {
              Box    box   = termShape->getBoundingBox ();
              QRect  rect = boxToScreenRect(box);
              painter.setPen( QPen( Qt::red ) );
              painter.setBrush(Qt::red);
              painter.drawRect(rect);
             
             

              continue;
            }
        }
    }
  }  // Netlist namespace.
}
