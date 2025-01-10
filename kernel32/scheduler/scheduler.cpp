class scheduler{
    public:
    process* tasks = nullptr;

    int create(){
        this->tasks = new process();
            this->tasks->status = READY;
    this->tasks->function = hello_world;
    return 0;
    }

    int execute(){
        if (tasks != nullptr)
            printf("RETURN VALUE: %d",tasks->function());
            return 0;
        return -1;
    }
};

