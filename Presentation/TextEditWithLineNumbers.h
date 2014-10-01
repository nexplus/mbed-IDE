#ifndef __TEXTEDIT_H__
#define __TEXTEDIT_H__

#include <QTextEdit>

#include "TextLineNumbers.h"

class TextEditWithLineNumbers : public QTextEdit
{
	Q_OBJECT

public:
    TextEditWithLineNumbers(QWidget *parent = 0)
    {
    	QTextEdit();
        m_lineNumbers = new TextLineNumbers(this);
    	connect(m_lineNumbers, SIGNAL( digitNumbersChanged() ), this, SLOT( slotAdjustSize() ) );
    	
    	setViewportMargins( m_lineNumbers->width(), 0, 0, 0 );
		m_lineNumbers->show();
    }

private:
    TextLineNumbers *m_lineNumbers;
  	
private slots:
	
	void slotAdjustSize()
	{
	    int margeGaucheSelection = 0;
	    int margeGaucheMargeNumerotation = 0;
	    //if ( m_selectionBorder )
	    //    margeGaucheSelection = 0;//m_selectionBorder->width();
	    
	    
	    //if ( m_lineNumbers )
	    margeGaucheMargeNumerotation = m_lineNumbers->width();
	    setViewportMargins( margeGaucheMargeNumerotation+margeGaucheSelection, 0, 0, 0 );
	}

   	void resizeEvent( QResizeEvent* e )
	{
	    QTextEdit::resizeEvent( e );
	    QRect margeNumerotationGeometry;	    
        margeNumerotationGeometry = QRect( viewport()->geometry().topLeft(), QSize( m_lineNumbers->width(), viewport()->height() ) );
        margeNumerotationGeometry.moveLeft( margeNumerotationGeometry.left() -m_lineNumbers->width() );
        if ( m_lineNumbers->geometry() != margeNumerotationGeometry )
            m_lineNumbers->setGeometry( margeNumerotationGeometry );
	    
	}
};

#endif // __TEXTEDIT_H__
