// Definition des paliers. Il y en a 4 pour le moment (i.e. 50, 65, 68, 77)
typedef enum { STATE_INITIAL, STATE_PALIER_1, STATE_PALIER_2, STATE_PALIER_3, STATE_PALIER_4, NUM_STATES } state_t;
typedef struct instance_data instance_data_t;
typedef state_t state_func_t( instance_data_t *data );

state_t do_state_initial( instance_data_t *data );
state_t do_state_foo( instance_data_t *data );
state_t do_state_bar( instance_data_t *data );