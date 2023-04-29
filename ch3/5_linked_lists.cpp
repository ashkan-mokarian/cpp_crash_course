/*
* Because references cannot be reseated, or be nullptr, we use pointers for 
* implementing linked lists instead of references.
*/
#include <cstdio>

/*
* Singly linked list: inserting in linked lists is very efficient. last element
* points to nullptr to indicate end of linked list. memory allocation is 
* discontinous.
*/
struct Element
{
    Element* next{};  // initialized with nullptr
    void insert_next(Element* new_element) {
        new_element->next = next;
        next = new_element;
    }
    char prefix[2];
    short operating_number;
};

int main() {
    Element trooper1, trooper2, trooper3;
    trooper1.prefix[0] = 'A';
    trooper1.prefix[1] = 'B';
    trooper1.operating_number = 101;
    trooper1.insert_next(&trooper2);
    trooper2.prefix[0] = 'M';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 102;
    trooper2.insert_next(&trooper3);
    trooper3.prefix[0] = 'X';
    trooper3.prefix[1] = 'Y';
    trooper3.operating_number = 103;

    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("Trooper %c%c, Nr:%d\n",
                cursor->prefix[0],
                cursor->prefix[1],
                cursor->operating_number);
    }

    // a point on references not reseatable
    int original = 100;
    int& original_ref = original;

    int newone = 200;
    original_ref = newone;  // pay attention. here reference is not reseating,
    // but changing the value of original. when a reference is initialized as a
    // reference, it always points to the same for the whole life cycle.
    printf("original:%d, orignial_ref:%d, newone:%d", original, original_ref, newone);

    return 0;
}
