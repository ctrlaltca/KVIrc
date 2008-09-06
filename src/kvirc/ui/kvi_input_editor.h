#ifndef _KVI_INPUT_EDITOR_H_
#define _KVI_INPUT_EDITOR_H_
//============================================================================
//
//   File : kvi_input_editor.h
//   Creation date : Fri Sep 5 2008 17:26:34 by Elvio Basello
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2008 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//============================================================================

#include "kvi_settings.h"
#include "kvi_pointerlist.h"
#include "kvi_string.h"
#include "kvi_window.h"

#include <QFrame>
#include <QString>
#include <QWidget>

class QKeyEvent;
class QDragEnterEvent;
class KviUserListView;
class KviTalPopupMenu;

// Default maximum buffer size.
#define KVI_INPUT_MAX_BUFFER_SIZE 400
// Border , better do not touch this
#define KVI_INPUT_BORDER 1
#define KVI_INPUT_MARGIN 2
// Cursor blink time...just don't set it to a value less than 100 if
// you don't want to be lagged by your cursors :)
#define KVI_INPUT_BLINK_TIME 800
// Drag scroll speed...(smaller values = faster)
#define KVI_INPUT_DRAG_TIMEOUT 80


class KVIRC_API KviInputEditor : public QFrame
{
	// friend class KviUserParser;
	//Q_PROPERTY( int KviProperty_FocusOwner READ heightHint )
	Q_PROPERTY( int TransparencyCapable READ heightHint )

	Q_OBJECT
public:
	KviInputEditor(QWidget * par, KviWindow * wnd, KviUserListView * view = 0);
	~KviInputEditor();
protected:

	QString                   m_szTextBuffer;
	int                       m_iCursorPosition;
	int                       m_iFirstVisibleChar;
	int                       m_iSelectionBegin;
	int                       m_iSelectionEnd;
	int                       m_iMaxBufferSize;
	bool                      m_bSpSlowFlag; // <-- what is this ?

	// members for supporting input methods
	QString                   m_szIMText;
	int                       m_iIMStart;
	int                       m_iIMLength;
	int                       m_iIMSelectionBegin;
	int                       m_iIMSelectionLength;
	bool                      m_bIMComposing;

	unsigned char             m_iCurFore;
	unsigned char             m_iCurBack;
	bool                      m_bCurBold;
	bool                      m_bCurUnderline;

	int                       m_iBlockLen;
	int                       m_iBlockWidth;
	bool                      m_bControlBlock;

	bool                      m_bCursorOn;

	int                       m_iCursorTimer;
	int                       m_iDragTimer;

	int                       m_iLastCursorXPosition;
	int                       m_iSelectionAnchorChar;

	// History stuff
	KviPointerList<QString> * m_pHistory;
	int                       m_iCurHistoryIdx;

	KviStr                    m_szSaveTextBuffer;

	// Nick completion
	KviUserListView         * m_pUserListView;
	QString                   m_szLastCompletedNick;
	QString                   m_szLastCompletionBuffer;
	int                       m_iLastCompletionCursorPosition;
	int                       m_iLastCompletionCursorXPosition;
	int                       m_iLastCompletionFirstVisibleChar;
	bool                      m_bLastCompletionFinished;

	bool                      m_bUpdatesEnabled;
	KviStr                    m_szAltKeyCode;
	KviWindow               * m_pKviWindow;
	QWidget                 * m_pInputParent;
	KviTalPopupMenu         * m_pIconMenu;
	bool                      m_bReadOnly;
public:
	int  heightHint() const;
	virtual QSize sizeHint() const;
	void setText(const QString text);
	QString text() { return m_szTextBuffer; };
	void insertChar(QChar c);
	void insertText(const QString & text);
	void applyOptions();
	void setMaxBufferSize(int size) { m_iMaxBufferSize = size; };
	void setReadOnly(bool bReadOnly) { m_bReadOnly = bReadOnly; };
	bool readOnly() { return m_bReadOnly; };
private:
	void replaceWordBeforeCursor(const QString & word, const QString & replacement, bool bRepaint = true);
	int replaceSegment(int start, int length, const QString & string);
	void getWordBeforeCursor(QString & buffer, bool * bIsFirstWordInLine);
	void runUpToTheFirstVisibleChar();
	void extractNextBlock(int idx, QFontMetrics & fm, int curXPos, int maxXPos);
	void drawTextBlock(QPainter * pa, QFontMetrics & fm, int curXPos, int textBaseline, int idx, int len, bool bSelected = false);
	QChar getSubstituteChar(unsigned short control_code);
	void moveRightFirstVisibleCharToShowCursor();
	void repaintWithCursorOn();
	void selectOneChar(int pos);
	int  charIndexFromXPosition(int xPos);
	int  xPositionFromCharIndex(QFontMetrics & fm, int chIdx, bool bContentsCoords = false);
	int  xPositionFromCharIndex(int chIdx, bool bContentsCoords = false);
	void killDragTimer();
	void handleDragSelection();
	void end();
	void home();
	bool hasSelection();
	void moveCursorTo(int idx,bool bRepaint = true);
	void returnPressed(bool bRepaint = true);
	void completion(bool bShift);
	void standardNickCompletion(bool bAddMask, QString & word, bool bFirstWordInLine);
	void recalcFontMetrics(QFontMetrics * pFm);
	void internalCursorRight(bool bShift);
	void internalCursorLeft(bool bShift);
public slots:
	void iconPopupActivated(int id);
	void copyToSelection(bool bDonNotCopyToClipboard = true);
	void copyToClipboard();
	void removeSelected();
	void cut();
	void pasteClipboardWithConfirmation();
	void pasteSelectionWithConfirmation();
	void pasteSlow();
	void stopPasteSlow();
	void pasteFile();
	void selectAll();
	void clear();
signals:
	void escapePressed();
	void enterPressed();
protected:
	virtual void drawContents(QPainter *);
	//virtual void resizeEvent(QResizeEvent *);
	virtual void timerEvent(QTimerEvent * e);
	virtual void focusInEvent(QFocusEvent * e);
	virtual void focusOutEvent(QFocusEvent *);
	virtual void keyPressEvent(QKeyEvent * e);
	virtual void keyReleaseEvent(QKeyEvent * e);
	virtual void mousePressEvent(QMouseEvent * e);
	virtual void mouseReleaseEvent(QMouseEvent * e);
	virtual void dragEnterEvent(QDragEnterEvent * e);
	virtual void dropEvent(QDropEvent * e);
	virtual void imStartEvent(QInputMethodEvent * e);
	virtual void imComposeEvent(QInputMethodEvent * e);
	virtual void imEndEvent(QInputMethodEvent * e);
	virtual void paintEvent(QPaintEvent * e);
};

#endif //_KVI_INPUT_EDITOR_H_
