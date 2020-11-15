class GameEngine {
    private:
        int total_score;

    public:
        int get_total_score() const;
        void game_start();
        void game_over();
        void spawn_enemy();
        void spawn_player();
        void update_score();
};