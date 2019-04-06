typedef struct {
	StateType nextState;
	void(*action)(void* UserData);
};