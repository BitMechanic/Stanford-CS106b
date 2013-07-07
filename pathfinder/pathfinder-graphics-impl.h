

class ButtonFunction {
public:
    virtual void execute() = 0;
};

class ButtonFunctionWithoutData : public ButtonFunction {
public:
    ButtonFunctionWithoutData(void (*fn)());
    virtual void execute();
    
private:
    void (*fn)();
};

template <typename ClientType>
class ButtonFunctionWithData : public ButtonFunction {
public:
    ButtonFunctionWithData(void (*fn)(ClientType &), ClientType *data) {
        this->fn = fn;
        this->data = data;
    }
    
    virtual void execute() {
        fn(*data);
    }
    
private:
    void (*fn)(ClientType &);
    ClientType *data;
};

class ClickFunction {
public:
    virtual void execute(const GPoint& pt) = 0;
};

class ClickFunctionWithoutData : public ClickFunction {
public:
    ClickFunctionWithoutData(void (*fn)(const GPoint& pt));
    virtual void execute(const GPoint& pt);
    
private:
    void (*fn)(const GPoint& pt);
};

template <typename ClientType>
class ClickFunctionWithData : public ClickFunction {
public:
    ClickFunctionWithData(void (*fn)(const GPoint& pt, ClientType&),
                          ClientType *data) {
        this->fn = fn;
        this->data = data;
    }
    
    virtual void execute(const GPoint& pt) {
        fn(pt, *data);
    }
    
private:
    void (*fn)(const GPoint&, ClientType &);
    ClientType *data;
};

/* Ignore everything from this part downward   */

void addButton(const string& name, ButtonFunction *fn);
void defineClickListener(ClickFunction *fn);

/*
 * Implementation notes: addButton, defineClickListener
 * ----------------------------------------------------
 * These template functions create the appropriate callback structure and
 * then call a non-template function in gpathfinder.cpp that works with
 * the base class of that object and therefore no longer requires the
 * overhead of C++'s template mechanism.
 */

template <typename ClientType>
void addButton(const string& name,
               void (*fn)(ClientType & data),
               ClientType & data) {
    addButton(name, new ButtonFunctionWithData<ClientType>(fn, &data));
}

template <typename ClientType>
void defineClickListener(void (*clickFn)(const GPoint& pt, ClientType & data),
                         ClientType & data) {
    defineClickListener(new ClickFunctionWithData<ClientType>(clickFn, &data));
}

