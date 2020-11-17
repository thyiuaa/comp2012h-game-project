class Unit {
    private:
        float hp;
        float attack;
        int velocity[2];
        int pos[2];
        int shooting_interval; // milisecond
    
    public:
        // constructers
        Unit();

        // accessor
        float get_hp() const;
        float get_attack() const;
        int* get_velocity() const;
        int* get_pos() const;
        int get_shooting_interval() const;

        void move();

        // pure virual funciton
        virtual void shoot() = 0; // player shoot when button pressed, enermy may shoot randomly 
        virtual void take_damage() = 0; // player can reduce damage by defensing
};