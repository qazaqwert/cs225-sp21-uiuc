
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    ListNode *position_;

public:
    ListIterator() : position_(NULL) {}
    ListIterator(ListNode *x) : position_(x) {}

    // Pre-Increment, ++iter
    ListIterator &operator++()
    {
        // @TODO: graded in MP3.1
        if (position_ == NULL)
        {
            return *this;
        }
        position_ = position_->next;

        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int)
    {

        // @TODO: graded in MP3.1
        if (position_ == NULL)
        {
            return *this;
        }
        ListNode *temp = position_;
        position_ = position_->next;
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator &operator--()
    {
        // @TODO: graded in MP3.1
        if (position_ == NULL)
        {
            return *this;
        }
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int)
    {
        // @TODO: graded in MP3.1
        if (position_ == NULL)
        {
            return *this;
        }
        ListNode *temp = position_;
        position_ = position_->prev;
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator &rhs)
    {
        // @TODO: graded in MP3.1
        if ((position_ == NULL && rhs.position_ != NULL) ||
            (position_ != NULL && rhs.position_ == NULL))
        {
            return true;
        }
        if (position_ == NULL && rhs.position_ == NULL)
        {
            return false;
        }
        if ((this->position_->next == rhs.position_->next) &&
            (this->position_->prev == rhs.position_->prev) &&
            (this->position_->data == rhs.position_->data))
        {
            return false;
        }
        return true;
    }

    bool operator==(const ListIterator &rhs)
    {
        return !(*this != rhs);
    }

    const T &operator*()
    {
        return position_->data;
    }

    const T *operator->()
    {
        return &(position_->data);
    }
};
