#include "rlinenumbers.h"
//
#include <QTextEdit>
#include <QGridLayout>
#include <QScrollBar>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QTextBlock>
#include <QDebug>
#include <QDialog>

LineNumbers::LineNumbers( QTextEdit* edit)
	: QWidget( (QWidget *)edit ), m_textEdit( edit )
{
	setObjectName( "editorZone" );
	setAutoFillBackground( true );
	connect( m_textEdit->document()->documentLayout(), SIGNAL( update( const QRectF& ) ), this, SLOT( update() ) );
	connect( m_textEdit->verticalScrollBar(), SIGNAL( valueChanged( int ) ), this, SLOT( update() ) );
	m_executedLine = 0;
	setDefaultProperties();	
	setMouseTracking( true );
}
//
void LineNumbers::paintEvent( QPaintEvent* )
{
	int contentsY = m_textEdit->verticalScrollBar()->value();
	qreal pageBottom = contentsY + m_textEdit->viewport()->height();
	int m_lineNumber = 1;
	const QFontMetrics fm = fontMetrics();
	const int ascent = fontMetrics().ascent() +1;
	
	QPainter p( this );
	for ( QTextBlock block = m_textEdit->document()->begin(); block.isValid(); block = block.next(), m_lineNumber++ )
	{
		QTextLayout* layout = block.layout();
		const QRectF boundingRect = layout->boundingRect();
		QPointF position = layout->position();
		if ( position.y() +boundingRect.height() < contentsY )
			continue;
		if ( position.y() > pageBottom )
			break;
		const QString txt = QString::number( m_lineNumber - 1 );
		
		p.drawText( width() -fm.width( txt ) - 2, qRound( position.y() ) -contentsY +ascent, txt ); // -fm.width( "0" ) is an ampty place/indent 		
	}
	p.end();
}

void LineNumbers::setDigitNumbers( int i )
{
	if ( i == mDigitNumbers )
		return;
	mDigitNumbers = i;
	setFixedWidth( fontMetrics().width( "0" ) * (i) + 22 ); // +2 = 1 empty place before and 1 empty place after 
	//setFixedWidth( fontMetrics().width( "0" ) * ( mDigitNumbers +2 ) ); // +2 = 1 empty place before and 1 empty place after
	emit digitNumbersChanged();
}
//
int LineNumbers::digitNumbers() const
{
	return mDigitNumbers;
}
//
void LineNumbers::setTextColor( const QColor& c )
{
	if ( c == mTextColor )
		return;
	mTextColor = c;
	QPalette p( palette() );
	p.setColor( foregroundRole(), mTextColor );
	setPalette( p );
	emit textColorChanged( mTextColor );
}
//
const QColor& LineNumbers::textColor() const
{
	return mTextColor;
}
//
void LineNumbers::setBackgroundColor( const QColor& c )
{
	if ( c == mBackgroundColor )
		return;
	mBackgroundColor = c;
	QPalette p( palette() );
	p.setColor( backgroundRole(), mBackgroundColor );
	setPalette( p );
	emit backgroundColorChanged( mBackgroundColor );
}
//
const QColor& LineNumbers::backgroundColor() const
{
	return mBackgroundColor;
}

void LineNumbers::setDefaultProperties()
{
	// Default properties
	setFont( m_textEdit->font() );
	setBackgroundColor( QColor( "#ffffd2" ) );
	//setTextColor( QColor( Qt::black ) );
	setTextColor( QColor( "#aaaaff" ) );
	setDigitNumbers( 4 );
}
