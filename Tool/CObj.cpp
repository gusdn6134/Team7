#include "pch.h"
#include "CObj.h"

void CObj::Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY)
{
    pOut->_11 *= _fX;
    pOut->_21 *= _fX;
    pOut->_31 *= _fX;
    pOut->_41 *= _fX;

    pOut->_12 *= _fY;
    pOut->_22 *= _fY;
    pOut->_32 *= _fY;
    pOut->_42 *= _fY;
}
