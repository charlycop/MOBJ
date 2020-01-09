// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  <vector>
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
    painter.setBackground( QBrush( Qt:: white ) );
    painter.eraseRect     ( QRect( QPoint (0,0), size() ) );
    painter.setPen( QPen( Qt::darkGreen , 1 ) );
    QRect  rect = boxToScreenRect(viewport_);
    painter.drawRect( rect  );
    painter.setPen   ( QPen   ( Qt::red , 0 ) );
    painter.setBrush(Qt::NoBrush);


    QFont font = painter.font();
    font.setPixelSize(12);
    painter.setFont(font);
    
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

  // Compte le nombre de fils sur un node
  int getNbLignes (vector<size_t>& lignes, size_t node_id){
      int nombre=0;
      for (auto& id : lignes)
        if (id == node_id)
          ++nombre;
      return nombre;
  }

  void   CellWidget ::query(unsigned  int flags , QPainter& painter) {
    if ((not  cell_) or (not  flags ))  {
     std::cout<< "HOLALA pas de CELL !" << std::endl;
       return;
    }

    //Pour tous les nets de la cell
    for(auto& net : cell_->getNets()){
        vector<size_t> lines;
        // Pour toutes les lines du net courant
        for(auto& line : net->getLines()){
            Point sourcePosition = line->getSourcePosition();
            Point targetPosition = line->getTargetPosition();

            // On cré un vecteur avec toutes les sources/targets
            lines.push_back(line->getSource()->getId());
            lines.push_back(line->getTarget()->getId());
            painter.setPen( QPen( Qt::cyan , 1 ) );
            painter.drawLine(xToScreenX(sourcePosition.getX()), yToScreenY(sourcePosition.getY()), xToScreenX(targetPosition.getX()), yToScreenY(targetPosition.getY()));
        }

        // Pour tous les nodes du net courant
        for(auto& node : net->getNodes()){
            if(node == nullptr || !node->getNet()
              || getNbLignes(lines, node->getId()) < 3) continue;

            QPoint position = pointToScreenPoint(node->getPosition());

            painter.setPen( QPen( Qt::cyan, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
            painter.drawPoint(position);
        }
    }

    
    const  vector <Instance*>& instances = cell_->getInstances ();
    LineShape* lineShape;
    ArcShape* arcShape;
    EllipseShape* ellipse;
    BoxShape* boxshape;
    TermShape* termShape;
    if (instances.size()){
      
      //Pour tous les terms de la cell
      for(auto& term : cell_->getTerms()){

        painter.setPen( QPen( Qt::red, 15) );
        Point inOutPosition(term->getPosition());
        painter.drawPoint(pointToScreenPoint(inOutPosition));

        inOutPosition.setY(inOutPosition.getY()-20);
        painter.drawText(pointToScreenPoint(inOutPosition), tr((term->getName()).c_str()));
      }
  
      for (auto& instance : instances) {
        
        Point instPos = instance->getPosition ();
        Point instTitlePos(instPos.getX(),instPos.getY()-20);
        painter.drawText(pointToScreenPoint(instTitlePos), tr(instance->getName().c_str()));

        const  Symbol* symbol   = instance->getMasterCell()->getSymbol();

        if (not symbol) continue;
        if (flags) {
         
          for (auto& shape : symbol->getShapes ()) {

            arcShape = dynamic_cast <ArcShape*>(shape);
            if (arcShape) {
              Box    box   = arcShape ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box.translate(instPos));
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawArc(rect, arcShape->getStart()*16 , arcShape->getSpan()*16 );   
              continue;
            }

            lineShape = dynamic_cast <LineShape*>(shape);
            if (lineShape) {

              int x1 = lineShape->getX1() + instPos.getX();
              int x2 = lineShape->getX2() + instPos.getX();
              int y1 = lineShape->getY1() + instPos.getY();
              int y2 = lineShape->getY2() + instPos.getY();

              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawLine(xToScreenX(x1), yToScreenY(y1), 
                               xToScreenX(x2), yToScreenY(y2));
              continue;
            }

            ellipse = dynamic_cast <EllipseShape*>(shape);
            if (ellipse) {
              Box    box   = ellipse ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box.translate(instPos));
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawEllipse(QRectF(rect));
              continue;
            }

            boxshape = dynamic_cast <BoxShape*>(shape);
            if (boxshape) {
              Box    box   = boxshape->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box.translate(instPos));
              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawRect(rect);
              continue;
            }

          }
          // On fait les terms a part pour qu'ils soient dessinés en dernier
          painter.setPen( QPen( Qt::red, 9) ); 
          for (auto& shape : symbol->getShapes ()) { 
            termShape = dynamic_cast <TermShape*>(shape);
            if (termShape) {
              Box    box   = termShape->getBoundingBox().translate(instPos);
              QRect  rect = boxToScreenRect(box);
              int flags[2];
              TermShape::toQtAlign(termShape->getAlign(), flags);
              painter.drawText(rect, flags[0]|flags[1], tr((termShape->getTerm()->getName()).c_str()));
              painter.drawPoint(rect.center());
              continue;
            }
          }
        }
      }
    }
    else{ // SI on a pas d'instances, on affiche les symboles de la cell_

        const  Symbol* symbol   = cell_->getSymbol ();
        painter.setPen( QPen( Qt::darkGreen , 3 ) );

        for (auto& shape : symbol->getShapes()) {
          
            lineShape = dynamic_cast <LineShape*>(shape);
            if (lineShape) {
              int x1 = lineShape->getX1();
              int x2 = lineShape->getX2();
              int y1 = lineShape->getY1();
              int y2 = lineShape->getY2();

              painter.setPen( QPen( Qt::darkGreen , 3 ) );
              painter.drawLine(xToScreenX(x1), yToScreenY(y1), 
                               xToScreenX(x2), yToScreenY(y2));
              continue;
            }

            arcShape = dynamic_cast <ArcShape*>(shape);
            if (arcShape) {
              Box    box   = arcShape ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box);
              painter.drawArc(rect, arcShape->getStart()*16 , arcShape->getSpan()*16 );   
              continue;
            }

            ellipse = dynamic_cast <EllipseShape*>(shape);
            if (ellipse) {
              Box    box   = ellipse ->getBoundingBox ();
              QRect  rect = boxToScreenRect(box);
              painter.drawEllipse(QRectF(rect));
              continue;
            }

            boxshape = dynamic_cast <BoxShape*>(shape);
            if (boxshape) {
              Box    box   = boxshape->getBoundingBox ();
              QRect  rect  = boxToScreenRect(box);
              painter.drawRect(rect);
              continue;
            }
        }

        // On fait les terms a part pour qu'ils soient dessinés en dernier
        painter.setPen( QPen( Qt::red, 9) ); 
        TermShape* termShape;
        for (auto& shape : symbol->getShapes()) { 
            termShape = dynamic_cast <TermShape*>(shape);
            if (termShape) { 
              Point position(termShape->getX1(), termShape->getY1());
              QPoint pos = pointToScreenPoint(position);
              painter.drawPoint(pos);
              continue;
            }
        }
     }
  }  // Netlist namespace.
}
