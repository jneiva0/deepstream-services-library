/*
The MIT License

Copyright (c) 2019-2023, Prominence AI, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _DSL_COND_H
#define _DSL_COND_H

#include "glib.h"
 
namespace DSL
{
    /**
     * @class DslCond
     * @brief Wrapper class for the GCond type
     */
    class DslCond
    {
    public:
    
        /**
         * @brief ctor for DslCond class
         */
        DslCond() 
        {
            g_cond_init(&m_cond);
        }
        
        /**
         * @brief dtor for DslMutex class
         */
        ~DslCond()
        {
            g_cond_clear(&m_cond);
        }
        
        /**
         * @brief & operator for the DslMutex class
         * @return returns the address of the wrapped mutex.
         */
        GCond* operator& ()
        {
            return &m_cond;
        }
        
    private:
        GCond m_cond; 
    };

} // namespace 

#endif // _DSL_COND_H