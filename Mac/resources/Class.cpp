#include "Class.hpp"

//---------------------------------------------------------------------------//
//                           CONSTRUCTORS / DESTRUCTOR                       //
//---------------------------------------------------------------------------//

Class::Class() {}

Class::Class(const Class &other)
{
	// copy members here
}

Class &Class::operator=(const Class &other)
{
	if (this != &other)
	{
		// copy members here
	}
	return (*this);
}

Class::~Class() {}

//---------------------------------------------------------------------------//
//                                PUBLIC METHODS                             //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//                               PRIVATE METHODS                             //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//                                 EXCEPTIONS                                //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//                                NON MEMBERS                                //
//---------------------------------------------------------------------------//