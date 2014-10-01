#ifndef LINENUMBERS_H
#define LINENUMBERS_H
//
#include <QWidget>
#include <QTextCursor>
//
class QTextEdit;

class LineNumbers : public QWidget
{
	Q_OBJECT
	Q_PROPERTY( int digitNumbers READ digitNumbers WRITE setDigitNumbers )
	Q_PROPERTY( QColor textColor READ textColor WRITE setTextColor )
	Q_PROPERTY( QColor backgroundColor READ backgroundColor WRITE setBackgroundColor )
	//
public:
	LineNumbers( QTextEdit* edit);
	//
	void setDigitNumbers( int );
	int digitNumbers() const;
	//
	void setTextColor( const QColor& );
	const QColor& textColor() const;
	//
	void setBackgroundColor( const QColor& );
	const QColor& backgroundColor() const;
	//
protected:
	virtual void paintEvent( QPaintEvent* );
	
private:
	QTextEdit* m_textEdit;	
	int mDigitNumbers;
	QColor mTextColor;
	QColor mBackgroundColor;
	int m_executedLine;
	int m_currentLine;
	QTextCursor m_cursor;
	//
signals:	
	void digitNumbersChanged();
	void textColorChanged( const QColor& );
	void backgroundColorChanged( const QColor& );
	
public slots:
	void setDefaultProperties();
};
//
#endif 

