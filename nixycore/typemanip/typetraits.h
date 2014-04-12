/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "nixycore/typemanip/typedetect.h"

#include "nixycore/general/general.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

/*
    Some functional features
*/

template <typename T>
struct traits
{
    typedef typename rm_reference<
            typename rm_cv<T>::type_t
    >::type_t type_t;

    typedef type_t*       point_t;
    typedef type_t&       refer_t;
    typedef const type_t* cpoint_t;
    typedef const type_t& crefer_t;

    typedef typename select_if<
            is_scalar<T>::value || is_reference<T>::value,
            T, 
            const typename rm_reference<
                  typename rm_const<T>::type_t>::type_t&
    >::type_t param_t;
};

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
