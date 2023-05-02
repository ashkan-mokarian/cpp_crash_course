/*
* You should use exception handling whenever possible (for establishing class 
* invariant). However, sometimes for legacy code, or embedded system design where
* real-time performance is important, other alternatives has to be used. More
* importantly (and more difficult), you have to check yourself that no memory
* is leaked.
*/

/*
* method 1: exposing a function that checks whether class invariant is established
*/
struct HumptyDumpty {
    HumptyDumpty();
    bool is_valid();
};
// In idiomatic C++, you will throw exception in constructor for class invariant
// checking. Here, you must always remember to check whether class invariant is 
// guaranteed.
bool do_sth() {
    HumptyDumpty hd{};
    if (!hd.is_valid()) return false;
    // class invariants are now guaranteed.
}

/*
* method 2: return multiple values using the language feature 'structure binding
* declaration' to return success flags alongside the usual return value.
*/
struct Result {
    HumptyDumpty hd;
    bool success;
};
Result make_humpty() {
    HumptyDumpty hd{};
    bool is_valid;
    // write code to check whether hd satisfies class invariant.
    return {hd, is_valid};
}
bool do_sth2() {
    auto [hd, success] = make_humpty();
    if (!success) return false;
    // class invariant is guaranteed.
    return true;
}