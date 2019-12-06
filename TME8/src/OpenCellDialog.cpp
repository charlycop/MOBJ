#include  <QLabel>
#include  <QLineEdit>
#include  <QPushButton>
#include  <QHBoxLayout>
#include  <QVBoxLayout>
#include "OpenCellDialog.h"

namespace Netlist{


    OpenCellDialog::OpenCellDialog ( QWidget* parent )
    : QDialog   (parent)
    , lineEdit_(NULL)
    {
        setWindowTitle( tr("Open Cell") );
        QLabel* label = new  QLabel();
        label ->setText( tr("Enter Cell name to open(without extention)") );
        lineEdit_ = new  QLineEdit();
        lineEdit_ ->setMinimumWidth( 400 );
        QPushButton* okButton = new  QPushButton();
        okButton ->setText( "OK" );
        okButton ->setDefault( true );
        QPushButton* cancelButton = new  QPushButton();
        cancelButton ->setText( "Cancel" );
        QHBoxLayout* hLayout = new  QHBoxLayout();
        hLayout ->addStretch();
        hLayout ->addWidget( okButton  );
        hLayout ->addStretch();
        hLayout ->addWidget( cancelButton  );
        hLayout ->addStretch();
        QFrame* separator = new  QFrame();
        separator ->setFrameShape( QFrame :: HLine );
        separator ->setFrameShadow( QFrame :: Sunken  );
        QVBoxLayout* vLayout = new  QVBoxLayout();
        vLayout ->setSizeConstraint( QLayout::SetFixedSize  );
        vLayout ->addWidget( label  );
        vLayout ->addWidget( lineEdit_  );
        vLayout ->addLayout( hLayout  );
        setLayout( vLayout  );
        connect( okButton     , SIGNAL(clicked ()), this , SLOT(accept ()) );
        connect( cancelButton , SIGNAL(clicked ()), this , SLOT(reject ()) );
    }

    bool OpenCellDialog::run(std::string* ptr){
        std::cout << "on rentre ici" << std::endl;
        int  dialogResult = exec();
        *ptr = getCellName().toStdString();
        if(ptr)
            return true;
        else
            std::cout << "Nom de cellule vide !" << std::endl;
        return false;
    }

    const  QString   OpenCellDialog :: getCellName  ()  const{
        return  lineEdit_ ->text(); 
    }

    void   OpenCellDialog :: setCellName ( const  QString& name ){
        return  lineEdit_ ->setText( name ); 
    }


} // Fin namespace Netlist