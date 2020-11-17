class Unit {
    protected:
        float hp;
        float attack;
        int velocity[2];
        int pos[2];
        int shooting_interval; // milisecond
        const int MAX_HP

    public:
        // constructer
        Unit(float hp, float attack, int velocity[2], int pos[2], int shooting_interval);

        // accessor
        float get_hp() const;
        float get_attack() const;
        int* get_velocity() const;
        int* get_pos() const;
        int get_shooting_interval() const;

        // mutator
        void move();

        // pure virual funciton
        virtual void shoot() = 0; // player shoot when button pressed, enermy may shoot randomly 
        virtual void take_damage(float raw_damage) = 0; // player can reduce damage by defensing
};