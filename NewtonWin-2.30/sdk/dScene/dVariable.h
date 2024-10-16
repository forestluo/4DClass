/////////////////////////////////////////////////////////////////////////////
// Name:        dVariable.h
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

#ifndef _D_VARIABLE_H_
#define _D_VARIABLE_H_

class dVariable
{	
	public:
	enum dType
	{
		m_int,
		m_float,
		m_string,
	};

	dVariable ();
	dVariable (const dVariable& me);
	virtual ~dVariable ();

	virtual dType GetType() const;

	virtual void SetName (const char* name);
	virtual const char* GetName() const;
	virtual void SetValue (int value);
	virtual void SetValue (float value);
	virtual void SetValue (const char* value);

	virtual int GetInt () const;
	virtual dFloat GetFloat () const;
	virtual const char* GetString () const;

	

	private:
	dType m_type;
	char m_name[64];
	union
	{
		char*	m_data;
		int		m_integer;
		dFloat	m_real;
	};	

	friend class dVariableList;
};

class dVariableList: public dTree<dVariable, unsigned>
{
	public:
	dVariableList();
	dVariableList(const dVariableList& me);
	virtual ~dVariableList ();

	virtual dVariable* CreateVariable (const char* name);

	virtual dVariable* FindVariable(unsigned crc) const;
	virtual dVariable* FindVariable(const char* name) const;

	virtual void Serialize(TiXmlElement* rootNode) const;
	virtual void Deserialize(TiXmlElement* rootNode);
	
	
};

#endif