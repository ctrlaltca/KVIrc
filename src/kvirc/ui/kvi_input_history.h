#ifndef _KVI_INPUT_HISTORY_H_
#define _KVI_INPUT_HISTORY_H_
//============================================================================
//
//   File : kvi_input_history.h
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

/**
* \file kvi_input_history.h
* \author Elvio Basello
* \brief Input history management
*/

#include "kvi_settings.h"
#include "kvi_pointerlist.h"

#define KVI_INPUT_MAX_GLOBAL_HISTORY_ENTRIES 100
#define KVI_INPUT_MAX_LOCAL_HISTORY_ENTRIES 20

/**
* \class KviInputHistory
* \brief Input history class
*/
class KVIRC_API KviInputHistory
{
private:
	static KviInputHistory * m_pSelf;
	static unsigned int      m_uCount;

	/**
	* \brief Constructs the input history object
	* \return KviInputHistory
	*/
	KviInputHistory();
protected:
	KviPointerList<QString> * m_pStringList;
public:
	/**
	* \brief Destroys the input history object
	*/
	~KviInputHistory();

	/**
	* \brief Initializes the class instance
	* \return void
	*/
	static void init();

	/**
	* \brief Destroys the class instance
	* \return void
	*/
	static void done();

	/**
	* \brief Returns the instance of the class
	* \return KviInputHistory *
	*/
	static inline KviInputHistory * instance(){ return m_pSelf; };

	/**
	* \brief Returns the number of instances of the class
	* \return unsigned int
	*/
	unsigned int count(){ return m_uCount; };

	/**
	* \brief Adds a reference to the class
	* \return void
	*/
	static void addRef();

	/**
	* \brief Removes a reference to the class
	* \return void
	*/
	static void delRef();

	/**
	* \brief Adds a string to the history
	* \param szString The string to add
	* \return void
	*/
	void add(QString * szString);

	/**
	* \brief Returns the list of string in the history
	* \return KviPointerList<QString> *
	*/
	KviPointerList<QString> * list(){ return m_pStringList; };

	/**
	* \brief Saves the history
	* \param szFileName The name of the file where to save
	* \return void
	*/
	void save(const QString & szFileName);

	/**
	* \brief Loads the history
	* \param szFileName The name of the file to load
	* \return void
	*/
	void load(const QString & szFileName);
};

#endif //_KVI_INPUT_HISTORY_H_
