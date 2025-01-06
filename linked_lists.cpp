#include <initializer_list>
#include <iostream>
#include <cassert>

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );
 
//Set class declaration
class Set {
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();
 
    // The instructions will describe exactly what to do
    Set( Set const &orig );
    Set( Set      &&orig );
 
    // The instructions will describe exactly what to do
    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );
 
    // Size operations
    bool        empty() const;
    std::size_t size()  const;
 
    // Clear all items out of the set
    void clear();
 
    // Find the value item in the set
    //  - Return the address of the node if found,
    //    and nullptr otherwise.
    Node *find( int const &item ) const;
 
    // Insert the item into the set if it
    // is not already in the set.
    //  - Return 1 if the item is new,
    //    and 0 otherwise.
    std::size_t insert( int const &item );
 
    // Insert all the items in the array
    // from array[begin] to array[end - 1]
    // that are not already in the set.
    //  - Return the number of items inserted
    //    into the set.
    std::size_t insert( int         const array[],
                        std::size_t const begin,
                        std::size_t const end );
 
    // Remove the item from the set and
    // return the number of items removed.
    std::size_t erase( int const &item );
 
    // Move any items from 'other', whose values
    // do not appear in 'this', to 'this'
    // Leave any items that already appear
    // in 'this' and 'other' in 'other'. 
    std::size_t merge( Set &other );

 
    // Set operations
    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );
 
    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;
 
    // Returns 'true' if the 'other' set
    // is a subset of 'this' set; that is,
    // all entries in the 'other' set are
    // also in this set.
    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;
 
    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;
   
  private:
    Node *p_head_;
 
  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};

//Node class declaration
class Node {
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;
 
  private:
    int   value_;
    Node *next_;

  // Allow any member function in the class
  // 'Set' to access or modify the member
  // variables of any instance of this class.
  friend class Set;
};

// Node class Definition
// Node constructor
Node::Node( int new_value, Node *new_next ):
value_ {new_value},
next_ {new_next} {
  // Empty constructor
}

int Node::value() const {
  return value_;
}

Node *Node::next() const {
  return next_;
}

//Set class definition
// Initializing constructor
Set::Set( std::initializer_list<int> initial_values):
p_head_ {nullptr} {
  for ( int const &value : initial_values ) {
    insert( value );
  }
}

// Destructor
Set::~Set() {
  clear();
}
 
// Copy constructor
Set::Set( Set const &orig ): 
p_head_{nullptr} {
    if (orig.p_head_ == nullptr) {
        return;
    }

    p_head_ = new Node(orig.p_head_->value(), nullptr);
    Node* current = p_head_; 
    Node* orig_current = orig.p_head_->next();

    //copy all the values
    while (orig_current != nullptr) {
        current->next_ = new Node(orig_current->value(), nullptr); 
        current = current->next_; 
        orig_current = orig_current->next();
    }
}

// Move constructor
Set::Set( Set &&orig ):
p_head_ {nullptr} {
  std::swap( p_head_, orig.p_head_ );
}
 
// Copy assignment
Set &Set::operator=( Set const &orig ) {
  //if they are the same, automatically skip to return
  if (this != &orig) {
    clear();
    //insert all the items
    for (Node *item = orig.p_head_; item != nullptr; item = item->next()) {
      insert(item->value()); 
    }
  }
  return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig ) {
  //if they are the same, automatically skip to return
  if (this != &orig) {
    //swap all the items
    std::swap( p_head_, orig.p_head_ ); 
  }
  return *this;
}
 
// Empty
bool Set::empty() const {
  return (p_head_ == nullptr);
}

// Size
size_t Set::size() const {
  size_t num {0};
  Node * current {p_head_};

  while (current != nullptr) {
    num++;
    current = current -> next_;
  }

  return num;
}
  
// Clear
void Set::clear() {
  while (!empty()){
    Node *temp = p_head_;
    p_head_ = p_head_->next();
    delete temp;
    temp = nullptr;
  }
}
 
// Find
Node *Set::find( int const &item ) const {
  Node * current {p_head_};

  while (current != nullptr) {
    if (current->value_ == item){
      return current;
    }
    current = current -> next_;
  }

  return nullptr;
}

// Insert the item into the set
std::size_t Set::insert( int const &item ) {
  if (find(item) != nullptr) {
    //item was found
    return 0;
  } else {
    //insert the item, point it to the original head
    Node * inserted_node = new Node(item, p_head_);
    p_head_ = inserted_node;
  
    return 1;
  }
}
 
// Insert all the items in the array
std::size_t Set::insert( int         const array[],
                         std::size_t const begin,
                         std::size_t const end ) {
  std::size_t count{0};
  for (std::size_t k{begin}; k < end; k++){
    //if the insertion was successful
    if (insert(array[k])){
      count++;
    }
  }
  return count;
}

// Remove the item from the set and
// return the number of items removed.
std::size_t Set::erase( int const &item ) {
  if (empty()) {
    return 0;
  }
  
  if (p_head_->value_ == item){
    //head is the item, deallocate head
    Node* temp = p_head_; 
    p_head_ = p_head_->next_;
    delete temp;
    temp = nullptr;

    return 1;
} 

  //loop to find the previous node
  Node* prev = p_head_;
  while (prev->next_ != nullptr) {
    if (prev->next_->value_ == item) {
      //previous node is found 
      Node* temp = prev->next_;
      prev->next_ = prev->next_->next_;
      delete temp;
      temp = nullptr;

      return 1;
    }
    prev = prev->next_;
  }

  //it is not in the list 
  return 0;
}
 
// Move any items from 'other', whose values
// do not appear in 'this', to 'this'.
// Leave any items that already appear
// in both sets, in both sets. 
std::size_t Set::merge( Set &other ) {
  std::size_t count{ 0 };
  
  Node * search {other.p_head_};
  Node * prev {};

  //search for each individual value in other until it ends
  while (search != nullptr){

    if ( !find(search->value_) ){
      //it is found, we need to move it
      //temperary variable to store the addess
      Node * to_move = search;

      if (prev == nullptr) {
        //the item we need to move is at the head, 
        //so we only need to update the head to the new value
        other.p_head_ = search->next_; 
      } else {
        //move the object by putting it after the previous node
        prev->next_ = search->next_; 
      }
      
      //update all the values for the loop
      search = search->next_;
      to_move->next_ = p_head_;
      p_head_ = to_move;

      count++;
    } else {
      //keep the node in other 
      prev = search; 
      search = search->next_;
    }
  }

  return count;
} 

// Set operations 
Set &Set::operator|=( Set const &other ) {
  for ( Node *ptr{ other.p_head_ }; ptr != nullptr; ptr = ptr->next_ ) {
    insert (ptr->value_);
  }
  return *this;
}
 
Set &Set::operator&=( Set const &other ) {
  Set tmp {}; 
  for ( Node *ptr = p_head_; ptr != nullptr; ptr = ptr->next_ ) {
    if (other.find(ptr->value_) != nullptr) {
      tmp.insert(ptr->value_);  // Insert only if common
    }
  }
  clear(); 
  return *this |= tmp;
}
 
Set &Set::operator^=( Set const &other ) {
  for ( Node *ptr{ other.p_head_ }; ptr != nullptr; ptr = ptr->next_ ) {
    if ( find(ptr->value_) ){
      erase (ptr->value_);
    } else {
      insert (ptr->value_);
    }
  }
  return *this;
}
 
Set &Set::operator-=( Set const &other ) {
  for ( Node *ptr{ other.p_head_ }; ptr != nullptr; ptr = ptr->next_ ) {
    erase (ptr->value_);
  }
  return *this;
}
 
Set Set::operator|( Set const &other ) const {
  Set result{*this};
  result |= other;
  return result;
}
 
Set Set::operator&( Set const &other ) const {
  Set result{*this};
  result &= other;
  return result;
}
 
Set Set::operator^( Set const &other ) const {
  Set result{*this};
  result ^= other;
  return result;
}
 
Set Set::operator-( Set const &other ) const {
  Set result{*this};
  result -= other;
  return result;
}
 
// Returns 'true' if the 'other' set
// is a subset of 'this' set; that is,
// all entries in the 'other' set are
// also in this set.
bool Set::operator>=( Set const &other ) const {
  Node *ptr = other.p_head_;
  for ( Node *ptr{ other.p_head_ }; ptr != nullptr; ptr = ptr->next_ ) {
    if (find(ptr->value_) == nullptr){
      return false;
    }
  }
  return true;
}
 
bool Set::operator<=( Set const &other ) const {
  return (other > *this);
}
 
bool Set::operator>( Set const &other ) const {
  return ((*this >= other) ^ (*this == other));
}
 
bool Set::operator<( Set const &other ) const {
  return ((other >= *this) ^ (*this == other));
}
 
bool Set::operator==( Set const &other ) const {
  if (size() != other.size()){
    return false;
  }

  Node *ptr = p_head_;
  for ( Node *ptr{ other.p_head_ }; ptr != nullptr; ptr = ptr->next_ ) {
    if (find(ptr->value_) == nullptr){
      return false;
    }
  }
  return true;
}
 
bool Set::operator!=( Set const &other ) const {
  return !(*this == other);
}


  ////////////////////////////////////////////
 /// Supplied Code for print Set objects  ///
////////////////////////////////////////////
/// @brief Overloads the << operator allowing the print of Set objects
/// @param out The ostream to print to (e.g. std::cout <<)
/// @param rhs The Set to print (e.g. << set_A)
/// @note You do not need to edit or alter this code
std::ostream &operator<<( std::ostream &out, Set const &rhs ) {
  out << "{";
  if ( !rhs.empty() ) {
    out << rhs.p_head_->value();   
    for ( Node *ptr{ rhs.p_head_->next() }; ptr != nullptr; ptr = ptr->next() ) {
      out << ", " << ptr->value();
    }
  }
  out << "}";
 
  return out;
}

int main() {

  return 0;
}
