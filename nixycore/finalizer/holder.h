/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "finalizer/refcounter.h"

#include "general/general.h"
#include "typemanip/typemanip.h"
#include "utility/utility.h"
#include "algorithm/algorithm.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

namespace private_holder
{
    template <typename T, class P, class Alloc_, class Model_>
    class detail : public RefBase<Alloc_, Model_>, public P
    {
        typedef RefBase<Alloc_, Model_> base_t;

    public:
        typedef T      type_t;
        typedef P      policy_t;
        typedef Model_ model_t;

    protected:
        type_t res_;

        template <typename F>
        void assign_to(const type_t& r, const F& dest_fr)
        {
            if (policy_t::is_valid(r))
            {
                base_t::init(dest_fr);
                res_ = r;
            }
        }

    public:
        detail(void)
        {
            policy_t::reset(res_);
        }

    public:
        void set(const type_t& r)
        {
            assign_to(r, make_destructor(r));
        }

        template <typename F>
        void set(const type_t& r, const F& dest_fr)
        {
            assign_to(r, make_destructor(r, dest_fr));
        }

        template <typename U>
        void set(const detail<U, P, Alloc_, Model_>& r)
        {
            if (base_t::set(r))
                res_ = (type_t)r.get();
            else
                policy_t::reset(res_);
        }

        void swap(detail& rhs)
        {
            base_t::swap(rhs);
            nx::swap(res_, rhs.res_);
        }

        type_t get(void) const { return res_; }
    };
}

/*
    Using reference counting to manage resources
*/

template <typename T, class P, class Alloc_ = NX_DEFAULT_ALLOC, class Model_ = NX_DEFAULT_THREAD_MODEL>
class holder
    : public RefCounter<private_holder::detail<T, P, Alloc_, Model_> >
    , public SafeBool<holder<T, P, Alloc_, Model_> >
{
    typedef RefCounter<private_holder::detail<T, P, Alloc_, Model_> > base_t;

public:
    holder(void)
        : base_t()
    {}
    template <typename U>
    holder(const U& r)
        : base_t(r)
    {}
    template <typename U, typename F>
    holder(const U& r, F dest_fr)
        : base_t(r, dest_fr)
    {}
    holder(const holder& r)
        : base_t(r)
    {}

    holder(const rvalue<holder>& r)
        : base_t()
    { nx::swap(*this, r); }

    holder& operator=(holder rhs)
    {
        rhs.swap(*this);
        return (*this);
    }

    bool checkSafeBool(void) const
    { return base_t::is_valid(base_t::get()); }

    void swap(holder& rhs) { base_t::swap(static_cast<base_t&>(rhs)); }
};

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////