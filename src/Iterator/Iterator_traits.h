/*
 @Date    : 2018-06-04 11:51:13
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
迭代器的traits类模板
 */

#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

namespace DSA
{
    struct seq_iterator_tag { static const char * what() { return "seq_Iterator"; }};
    struct bi_iterator_tag: public seq_iterator_tag
    { static const char * what() { return "bi_Iterator"; }};
    struct random_iterator_tag: public bi_iterator_tag
    { static const char * what() { return "random_Iterator"; }};

    template <typename It>
    struct Iterator_traits
    {
        typedef typename It::iterator_category iterator_category;
    };

    template <typename T>
    struct Iterator_traits<T*>
    {
        typedef random_iterator_tag iterator_category;
    };

} // DSA

#endif // ITERATOR_TRAITS_H


