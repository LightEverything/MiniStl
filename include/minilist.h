/**
 * @file minilist.h
 * @author lightevething (wanxinnb@outlook.com)
 * @brief 标准gnc的list是使用循环链表构成的，由于循环链表的复杂性，我个人建议仔细去网上学习(这样求begin和end就是O（1）的时间复杂度)
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __MINI_LIST__H
#define __MINI_LIST___H

#include <memory>
#define __DEFAULT_ALLOCATOR std::allocator<__MiniList_Node<T>>
#define __LIST_NULL_DATA 0

namespace MiniStd
{
    // std的定义我懒得继承， 直接搬过来用
    struct input_iterator_tag {};

    struct output_iterator_tag {};

    struct forward_iterator_tag : input_iterator_tag {};

    struct bidirectional_iterator_tag : forward_iterator_tag {};

    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    struct list_difference_type {};
}

namespace MiniStd
{
    template<typename T>
    struct __MiniList_Node
    {
        using nodeptr = __MiniList_Node<T>* ;
        nodeptr pre;
        nodeptr next;
        T node_data;
    };

    template<typename T>
    class __MiniList_Iterator
    {
    public:
        // 用于traits
        using value_type      = T;
        using difference_type = list_difference_type;
        using iterator_category = bidirectional_iterator_tag;
        using pointer         = T*;
        using reference       = T&;

        // 用nodeptr减少代码量
        using nodeptr = __MiniList_Node<T>* ;
        using selfreference = __MiniList_Iterator<T>& ;
        using selfpointer = __MiniList_Iterator<T>* ;
        using selfvalue = __MiniList_Iterator<T> ;

        __MiniList_Iterator(nodeptr ptr) : node_ptr(ptr) {}
        void* data() const { return (void*)node_ptr;}
        ~__MiniList_Iterator() {}
        // 运算符重载
        reference operator*() { return node_ptr->node_data;}
        pointer operator->() { return &(node_ptr->node_data);}
        // 自增运算符(前后)
        const selfvalue operator++(int) noexcept{ auto tmp = *this; ++node_ptr; return tmp;}
        selfreference operator++() noexcept { node_ptr = node_ptr->next; return *this;} 
        const selfvalue operator--(int) noexcept{ auto tmp = *this; --node_ptr; return tmp;}
        selfreference operator--() noexcept { node_ptr = node_ptr->pre; return *this;}
    private:
        nodeptr node_ptr;
    };

    template<typename T, typename alloc = __DEFAULT_ALLOCATOR>
    class MiniList
    {
    public:
        using iterator = __MiniList_Iterator<T>;
        using nodeptr = __MiniList_Node<T>* ;

        // 申请头指针内存
        MiniList()
        {
            alloc al;
            head_ptr = al.allocate(1);
            head_ptr->next = head_ptr, head_ptr->pre = head_ptr, head_ptr->node_data = __LIST_NULL_DATA;
        }

        iterator begin() { return iterator(head_ptr->pre);}
        iterator end(){ return iterator(head_ptr);}
        /**
         * @brief 
         * @todo insert的构建
         * @param data 
         * @return iterator 
         */
        iterator insert(T& data) 
        {
            auto pre = end(), it = end();
            pre --;

        }
        ~MiniList() {}
    private:
        nodeptr head_ptr;
    };
}

#endif