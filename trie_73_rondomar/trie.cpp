#include "trie.hpp"

#include <utility>
#include <algorithm>
#include <cassert>

bool trie::insert(const std::string& str) {
    trie_node *current_node = m_root;
    if(contains(str)){
        return false;
    }
    if(str.empty()){
        current_node->children[0]= new trie_node;
        current_node->children[0]->parent= current_node;
        current_node->children[0]->is_terminal=true;
        m_size++;
        return true;
    }
    for (char i : str) {
        // create a new node if the path doesn't exist
        if (current_node->children[i] == nullptr) {
            current_node->children[i] = new trie_node;
            current_node->children[i]->payload=i;
            current_node->children[i]->parent= current_node;
        }
        current_node = current_node->children[i];
    }
    current_node->is_terminal=true;
    m_size++;
    return true;
}

bool trie::erase(const std::string& str){
    if(!contains(str)) {
        return false;
    }
    trie_node *current_node = m_root;
    for (char i : str) {
        current_node = current_node->children[i];
    }
    current_node->is_terminal=false;
    for(int i = 0; i<str.length(); i++) {
        bool has_children = false;
        for (auto & j : current_node->children) {
            if (j != nullptr) {
                has_children = true;
            }
        }
        if (!has_children) {
            char node_character = current_node->payload;
            current_node = current_node->parent;
            delete current_node->children[node_character];
            current_node->children[node_character]= nullptr;
        }
    }
    m_size--;
    return true;
}

bool trie::contains(const std::string& str) const{
    trie_node *current_node = m_root;
    if(str.empty() and current_node->children[0]== nullptr){
        return false;
    }
    for(int i=0;i<str.length();i++){
        current_node = current_node->children[str[i]];
        if(nullptr == current_node){
            return false;
        }
        if (i==(str.length()-1) and !current_node->is_terminal){
            return false;
        }
    }
    return true;
}

trie::trie(){
    m_root = new trie_node;
    m_size = 0;
}

trie::trie(const std::vector<std::string>& strings){
    m_root = new trie_node;
    m_size = 0;
    for(const auto & string : strings){
        insert(string);
    }
}
//copy constructor
trie::trie(const trie& rhs){
    if(rhs.m_root== nullptr){
        m_size=0;
        m_root = nullptr;
    }
    else if(rhs.m_size==0){
        m_size = 0;
        m_root = new trie_node;
    }
    else {
        m_size = 0;
        m_root = new trie_node;
        trie_node *current_node = rhs.m_root;
        if (current_node->children[0] != nullptr) {
            current_node = current_node->children[0];
            goto begin_done;
        }
        while (true) {
            for (int i = 0; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    current_node = current_node->children[i];
                    if (current_node->is_terminal) {
                        goto begin_done;
                    }
                }
            }
        }
        begin_done:
        const_iterator iterator(current_node);
        insert((*iterator));
        for(int i = 1; i<rhs.m_size;i++){
            ++iterator;
            insert(*iterator);
        }
    }
}/* {
    m_root = rhs.m_root;
    m_size = rhs.m_size;
    trie_node *current_node = m_root;
    trie_node *rhs_node = rhs.m_root;
    for(int i =0; i<num_chars; i++){
        if(rhs.m_root->children[i]!= nullptr){
            rhs_node = rhs_node->children[i];
            current_node->children[i] = rhs_node;
            while(1){
                bool has_children = false;
                for(int i=0;i<num_chars;i++){
                    if(rhs_node->children[i] != nullptr){
                        rhs_node = rhs_node->children[i];
                        current_node->children[i] = rhs_node;
                    }
                }
                break;
            }

        }

    }
}*/
//scuffed move constructor
trie::trie(trie&& rhs){
    //delete old this
    if (m_size == 0) {
        delete m_root;
        m_root = nullptr;
    } else {
        trie_node *current_node = m_root;
        if (m_root->children[0] != nullptr) {
            delete m_root->children[0];
            m_root->children[0] = nullptr;
        }
        char previous_payload = 1;

        while (true) {
            bool has_children = false;
            for (int i = previous_payload + 1; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    has_children = true;
                    current_node = current_node->children[i];
                    break;
                }
            }
            if (!has_children) {
                if (current_node == m_root) {
                    delete m_root;
                    m_root = nullptr;
                    //delete m_root;
                    //m_root = nullptr;
                    break;
                }
                //delete[] current_node->children;
                char payload = current_node->payload;
                current_node = current_node->parent;
                delete current_node->children[payload];
                current_node->children[payload] = nullptr;
                previous_payload = payload;
            } else { previous_payload = 1; }
        }
    }
    //copy rhs to this
    trie t1(rhs);
    *this = t1;
    //now delete rhs
    if (rhs.m_size == 0) {
        delete rhs.m_root;
        rhs.m_root = nullptr;
    } else {
        trie_node *current_node = rhs.m_root;
        if (rhs.m_root->children[0] != nullptr) {
            delete rhs.m_root->children[0];
            rhs.m_root->children[0] = nullptr;
        }
        char previous_payload = 1;

        while (true) {
            bool has_children = false;
            for (int i = previous_payload + 1; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    has_children = true;
                    current_node = current_node->children[i];
                    break;
                }
            }
            if (!has_children) {
                if (current_node == rhs.m_root) {
                    delete rhs.m_root;
                    rhs.m_root = nullptr;
                    //delete m_root;
                    //m_root = nullptr;
                    break;
                }
                //delete[] current_node->children;
                char payload = current_node->payload;
                current_node = current_node->parent;
                delete current_node->children[payload];
                current_node->children[payload] = nullptr;
                previous_payload = payload;
            } else { previous_payload = 1; }
        }
    }
}

//destructor
trie::~trie() {
    if(m_root == nullptr){
        m_size = 0;
    }
    /*else if (m_size == 0) {
        delete m_root;
    } */else {
        trie_node *current_node = m_root;
        if (m_root->children[0] != nullptr) {
            delete m_root->children[0];
            m_root->children[0] = nullptr;
        }
        char previous_payload = 1;

        while (true) {
            bool has_children = false;
            for (int i = previous_payload + 1; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    has_children = true;
                    current_node = current_node->children[i];
                    break;
                }
            }
            if (!has_children) {
                if (current_node == m_root) {
                    current_node = m_root;
                    m_root = nullptr;
                    delete current_node;
                    //delete m_root;
                    //m_root = nullptr;
                    break;
                }
                //delete[] current_node->children;
                char payload = current_node->payload;
                current_node = current_node->parent;
                delete current_node->children[payload];
                current_node->children[payload] = nullptr;
                previous_payload = payload;
            } else { previous_payload = 1; }
        }
    }
}


trie &trie::operator=(const trie &rhs){
    //if self assignment
    if(*this == rhs){
        return *this;
    }
    //delete old data
    if(m_root == nullptr){
        m_size = 0;
    }
    /*else if (m_size == 0) {
    delete m_root;
    } */
    else {
        trie_node *current_node = m_root;
        if (m_root->children[0] != nullptr) {
            delete m_root->children[0];
            m_root->children[0] = nullptr;
        }
        char previous_payload = 1;

        while (true) {
            bool has_children = false;
            for (int i = previous_payload + 1; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    has_children = true;
                    current_node = current_node->children[i];
                    break;
                }
            }
            if (!has_children) {
                if (current_node == m_root) {
                    current_node = m_root;
                    m_root = nullptr;
                    delete current_node;
                    //delete m_root;
                    //m_root = nullptr;
                    break;
                }
                //delete[] current_node->children;
                char payload = current_node->payload;
                current_node = current_node->parent;
                delete current_node->children[payload];
                current_node->children[payload] = nullptr;
                previous_payload = payload;
            } else { previous_payload = 1; }
        }
    }
    //assign data
    if(rhs.m_root== nullptr){
        m_size=0;
        m_root = nullptr;
    }
    else if(rhs.m_size==0){
        m_size = 0;
        m_root = new trie_node;
    }
    else {
        m_size = 0;
        m_root = new trie_node;
        trie_node *current_node = rhs.m_root;
        if (current_node->children[0] != nullptr) {
            current_node = current_node->children[0];
            goto begin_done;
        }
        while (true) {
            for (int i = 0; i < num_chars; i++) {
                if (current_node->children[i] != nullptr) {
                    current_node = current_node->children[i];
                    if (current_node->is_terminal) {
                        goto begin_done;
                    }
                }
            }
        }
        begin_done:
        const_iterator iterator(current_node);
        insert((*iterator));
        for(int i = 1; i<rhs.m_size;i++){
        ++iterator;
        insert(*iterator);
        }
    }
    return *this;
}

//move operator
trie &trie::operator=(trie &&rhs){
    if(*this != rhs) {
        //destroy existing data in this
        if (m_root == nullptr) {
        }
        else if (m_size == 0) {
            delete m_root;
            m_root= nullptr;
        } else {
            m_size = 0;
            trie_node *current_node = m_root;
            if (m_root->children[0] != nullptr) {
                delete m_root->children[0];
                m_root->children[0] = nullptr;
            }
            char previous_payload = 1;

            while (true) {
                bool has_children = false;
                for (int i = previous_payload + 1; i < num_chars; i++) {
                    if (current_node->children[i] != nullptr) {
                        has_children = true;
                        current_node = current_node->children[i];
                        break;
                    }
                }
                if (!has_children) {
                    if (current_node == m_root) {
                        current_node = m_root;
                        m_root = nullptr;
                        delete current_node;
                        //delete m_root;
                        //m_root = nullptr;
                        break;
                    }
                    //delete[] current_node->children;
                    char payload = current_node->payload;
                    current_node = current_node->parent;
                    delete current_node->children[payload];
                    current_node->children[payload] = nullptr;
                    previous_payload = payload;
                } else { previous_payload = 1; }
            }
        }

        //move to this
        const trie& t1(rhs);
        *this = rhs;
        return *this;
    }
    else{
        return rhs;
    }
}

size_t trie::size() const {
    return m_size;
}


bool trie::empty() const {
    return m_size==0;
}

std::vector<std::string> trie::search_by_prefix(const std::string &prefix) const {
    std::vector<std::string> result;
    if(empty()){
        return result;
    }
    const_iterator iter = this->begin();
    while(iter!= nullptr){
        std::string iter_string = *iter;
        auto res = std::mismatch(prefix.begin(), prefix.end(), iter_string.begin());
        if(res.first == prefix.end()){
            //prefix is a prefix of iter_string
            result.push_back(iter_string);
        }
        ++iter;
    }
    return result;
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    std::vector<std::string> result;
    if(empty()){
        return result;
    }
    const_iterator iter = this->begin();
    while(iter!= nullptr){
        std::string iter_string = *iter;
        auto res = std::mismatch(iter_string.begin(), iter_string.end(), str.begin());
        if(res.first == iter_string.end()){
            //prefix is a prefix of iter_string
            result.push_back(iter_string);
        }
        ++iter;
    }
    return result;
}

trie::const_iterator trie::begin() const {
    if (empty()) {
        return nullptr;
    }
    trie_node *current_node = m_root;
    if(current_node!= nullptr) {
        if (current_node->children[0] != nullptr) {
            current_node = current_node->children[0];
            return current_node;
        }
    }
    while (true) {
        for (int i = 0; i < num_chars; i++) {
            if (current_node->children[i] != nullptr) {
                current_node = current_node->children[i];
                if(current_node->is_terminal) {
                    goto finished;
                }
                i=0;
            }
        }
    }
    finished:
    return current_node;
}

trie::const_iterator trie::end() const {
    return nullptr;
}

void trie::swap(trie &rhs) {
    trie temp =*this;
    *this = rhs;
    rhs = temp;
}

bool trie::operator==(const trie &rhs) const {
    if(empty() and rhs.empty()){
        return true;
    }
    const_iterator iter1(m_root);
    const_iterator iter2(rhs.m_root);
    while(iter1 != this->end() or iter2 != rhs.end()){
        if(iter1 != iter2){
            return false;
        }
        ++iter1;
        ++iter2;
    }
    return true;
}




trie::const_iterator::const_iterator(const trie_node *node) {
    current_node = node;
}

trie::const_iterator &trie::const_iterator::operator++() {
    bool child_found = false;
    //current node has children
    for(int i=0; i<num_chars;i++){
        if(current_node->children[i] != nullptr){
            current_node = current_node->children[i];
            if(current_node->is_terminal){
                const_iterator temp(current_node);
                *this = temp;
                return *this;
            }
            while(!current_node->is_terminal) {
                for (int j = 0; j < num_chars; j++) {
                    if (current_node->children[j] != nullptr) {
                        current_node = current_node->children[j];
                    }
                }
                const_iterator temp(current_node);
                *this = temp;
                return *this;
            }
        }
    }
    //current node has to go up
    while(true) {
        for (int i = current_node->payload+1; i < num_chars; i++) {
            if (current_node->parent->children[i] != nullptr) {
                child_found = true;
                current_node = current_node->parent->children[i];
                goto children_found;
            }
        }
        //reaching root while going up from depth 2
        if(current_node->parent->parent== nullptr) {
            // look for other children in depth 1
            bool depth_one_has_other_children = false;
            for (int i = current_node->payload + 1; i < num_chars; i++) {
                if (current_node->parent->children[i] != nullptr) {
                    child_found = true;
                    depth_one_has_other_children = true;
                    current_node = current_node->parent->children[i];
                    goto children_found;
                }
            }
            //look for other root children
            /*bool root_has_other_children = false;
            for(int i = current_node->parent->payload+1; i<num_chars; i++){
                if(current_node->parent->parent->children[i]!= nullptr){
                    child_found=true;
                    root_has_other_children = true;
                    current_node = current_node->parent->parent->children[i];
                    goto children_found;
                }
            }*/
            //no other children exist
            const_iterator temp(nullptr);
            *this = temp;
            return *this;
        }
        current_node = current_node->parent;
    }
    children_found:
    //current node has children
    if(current_node->is_terminal){
        const_iterator temp(current_node);
        *this = temp;
        return *this;
    }
    while(!current_node->is_terminal){
        for(int i=0;i<num_chars;i++){
            if(current_node->children[i]!= nullptr){
                current_node=current_node->children[i];
            }
        }
    }

    const_iterator temp(current_node);
    *this = temp;
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int) {
    const_iterator orig = *this;
    bool child_found = false;
    //current node has children
    for(int i=0; i<num_chars;i++){
        if(current_node->children[i] != nullptr){
            current_node = current_node->children[i];
            if(current_node->is_terminal){
                const_iterator temp(current_node);
                *this = temp;
                return orig;
            }
            while(!current_node->is_terminal) {
                for (int j = 0; j < num_chars; j++) {
                    if (current_node->children[j] != nullptr) {
                        current_node = current_node->children[j];
                    }
                }
                const_iterator temp(current_node);
                *this = temp;
                return orig;
            }
        }
    }
    //current node has to go up
    while(!child_found) {
        for (int i = current_node->payload+1; i < num_chars; i++) {
            if (current_node->parent->children[i] != nullptr) {
                child_found = true;
                current_node = current_node->parent->children[i];
                goto children_found;
            }
        }
        //reaching root while going up from depth 2
        if(current_node->parent->parent== nullptr) {
            // look for other children in depth 1
            bool depth_one_has_other_children = false;
            for (int i = current_node->payload + 1; i < num_chars; i++) {
                if (current_node->parent->children[i] != nullptr) {
                    child_found = true;
                    depth_one_has_other_children = true;
                    current_node = current_node->parent->children[i];
                    goto children_found;
                }
            }
            //look for other root children
            /*bool root_has_other_children = false;
            for(int i = current_node->parent->payload+1; i<num_chars; i++){
                if(current_node->parent->parent->children[i]!= nullptr){
                    child_found=true;
                    root_has_other_children = true;
                    current_node = current_node->parent->parent->children[i];
                    goto children_found;
                }
            }*/
            //no other children exist
            if (!(depth_one_has_other_children/* or root_has_other_children*/)) {
                const_iterator temp(current_node->parent->parent);
                *this = temp;
                return orig;
            }
        }
        current_node = current_node->parent;
    }
    children_found:
    //current node has children
    if(current_node->is_terminal){
        const_iterator temp(current_node);
        *this = temp;
        return orig;
    }
    while(!current_node->is_terminal){
        for(int i=0;i<num_chars;i++){
            if(current_node->children[i]!= nullptr){
                current_node=current_node->children[i];
            }
        }
    }

    const_iterator temp(current_node);
    *this = temp;
    return orig;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    if(current_node->parent == nullptr){
        return "";
    }
    trie_node const *temp_node = current_node;
    if(current_node->payload==0){
        return "";
    }
    std::string held_string;
    while(temp_node->parent!= nullptr){
        held_string.insert(0, &temp_node->payload, 1);
        temp_node = temp_node->parent;
    }
    return held_string;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    if (current_node == nullptr and rhs.current_node == nullptr) {
        return true;
    }
    if(current_node == nullptr or rhs.current_node == nullptr){
        return false;
    }
    if (rhs.current_node->payload != current_node->payload) {
        return false;
    }
    if(rhs.current_node->parent != nullptr and current_node->parent != nullptr){
        if (rhs.current_node->parent->payload != current_node->parent->payload) {
            return false;
        }
    }
    for(int i = 0; i<num_chars; i++){
        if(this->current_node->children[i] == nullptr or rhs.current_node->children[i] == nullptr){
            if(!(this->current_node->children[i] == nullptr and rhs.current_node->children[i] == nullptr)){
                return false;
            }
        }
        else if(this->current_node->children[i]->payload != rhs.current_node->children[i]->payload){
            return false;
        }
    }
    return true;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return !(*this == rhs);
}

bool has_children(trie_node node, char start) {
    bool has_children = false;
    for (int i = start; i < num_chars; i++) {
        if (node.children[i] != nullptr) {
            has_children=true;
        }
    }
    return has_children;
}

/**
 * Vrací `true` pokud je tato trie menší než `rhs`.
 *
 * Trie jsou porovnávány tak, že všechny řetězce v lexikografickém pořadí
 * se porovnají lexikograficky.
 * To znamená, že ["abc"] < ["abc", "b"], ["aac", "b"] < ["abc", "b"].
 */
bool trie::operator<(const trie &rhs) const {
    const_iterator iter2 = rhs.begin();
    const_iterator iter1 = this->begin();
    //if at least one trie is empty
    if(iter1 == nullptr or iter2 == nullptr){
        //second is empty first one not
        if(iter1 != nullptr){
            return false;
        }
        //first one empty
        if(iter2 != nullptr){
            return true;
        }
        //both empty
        return false;
    }
    //both trie not empty
    while(iter1 != nullptr and iter2 != nullptr){
        std::string string1 = *iter1;
        std::string string2 = *iter2;
        if(string1 == string2){
            ++iter1;
            ++iter2;
        }
        //theres a difference
        else{
            return (std::lexicographical_compare(string1.begin(), string1.end(), string2.begin(), string2.end()));
        }
    }
    //reached end of at least one iter
    //if at least one trie is empty
    //second is empty first one not
    if(iter1 != nullptr){
        return false;
    }
    //first one empty
    if(iter2 != nullptr){
        return true;
    }
    //both empty
    return false;
}


trie trie::operator|(const trie &rhs) const {
    return trie();
}

trie trie::operator&(const trie &rhs) const {
    return trie();
}

//! 2 trie jsou si nerovné právě tehdy, když si nejsou rovné (viz operator==)
bool operator!=(const trie& lhs, const trie& rhs){
    return !(lhs==rhs);
}
//! Lexicografické uspořádání, viz operator<
bool operator<=(const trie& lhs, const trie& rhs){
    trie::const_iterator iter2 = rhs.begin();
    trie::const_iterator iter1 = lhs.begin();
    //if at least one trie is empty
    if(iter1 == nullptr or iter2 == nullptr){
        //second is empty first one not
        if(iter1 != nullptr){
            return false;
        }
        //first one empty
        if(iter2 != nullptr){
            return true;
        }
        //both empty
        return true;
    }
    //both trie not empty
    while(iter1 != nullptr and iter2 != nullptr){
        std::string string1 = *iter1;
        std::string string2 = *iter2;
        if(string1 == string2){
            ++iter1;
            ++iter2;
        }
            //theres a difference
        else{
            return (std::lexicographical_compare(string1.begin(), string1.end(), string2.begin(), string2.end()));
        }
    }
    //reached end of at least one iter
    //if at least one trie is empty
    //second is empty first one not
    if(iter1 != nullptr){
        return false;
    }
    //first one empty
    if(iter2 != nullptr){
        return true;
    }
    //both empty
    return true;
}

//! Lexicografické uspořádání, viz operator<
bool operator>(const trie& lhs, const trie& rhs){
    return !(lhs<=rhs);
}
//! Lexicografické uspořádání, viz operator<
bool operator>=(const trie& lhs, const trie& rhs){
    return !(lhs<rhs);
}

std::ostream& operator<<(std::ostream& out, trie const& trie){
    return (std::ostream &) "";
}
