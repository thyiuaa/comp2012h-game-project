#include "Unit.h"

class Player : public Unit {
    private:
        float defense;
    
    public:
        bool is_defensing() const;
};