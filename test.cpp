#include <iostream>

using namespace std;

class Widget
{
public:
    Widget()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    Widget(const Widget & widget)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    Widget(Widget && widget)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    auto operator =(Widget const & widget) -> Widget &
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }
        
    auto operator =(Widget && widget) -> Widget &
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }
        
};
        
void f(Widget & w)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void f(Widget && w)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

        
Widget simpleMakeWidget()
{
    return Widget();
}
        
Widget complexMakeWidget()
{
    Widget w1 = Widget();
    Widget w2 = Widget();
    
    return rand() ? w1 : w2;
}
        
Widget & makeWidgetAndReturnLvalueReference()
{
    Widget * w1 = new Widget();
    Widget * w2 = new Widget();
    
    return rand() ? *w1 : *w2;
}
        
Widget && makeWidgetAndReturnRvalueReference()
{
    Widget w1 = Widget();
    Widget w2 = Widget();
    
    return rand() ? move(w1) : move(w2);
}
        
int main(int argc, const char * argv[]) {
    
    //lvalue-объект
    Widget w;
    {
        Widget lvo { w };
        Widget & lvo_lvr { w };
        Widget && lvo_rvr { w };
    }
    f(w);
    
    //lvalue-объект типа lvalue-ссылка
    Widget & x { w };
    {
        Widget lvo {x};
        Widget & lvo_lvr {x};
        Widget && lvo_rvr { x };
    }
    f(x);
    
    //lvalue-объект типа rvalue-ссылка
    Widget && y {move(w)};
    {
        Widget lvo { move(y) };
        Widget & lvo_lvr {y};
        Widget && lvo_rvr = { y };
    }
    f(y);
    
    //rvalue-объект
    {
        Widget lvo { complexMakeWidget() };
        Widget & lvo_lvr { complexMakeWidget() };
        Widget && lvo_rvr { complexMakeWidget() };
    }
    {
        Widget lvo { simpleMakeWidget() };
    }
    f(complexMakeWidget());
    
    //rvalue-объект типа lvalue-ссылка
    {
        Widget lvo { makeWidgetAndReturnLvalueReference() };
        Widget & lvo_lvr { makeWidgetAndReturnLvalueReference() };
        Widget && lvo_rvr = makeWidgetAndReturnLvalueReference();
    }
    f(makeWidgetAndReturnLvalueReference());
    
    //rvalue-объект типа rvalue-ссылка
    {
        Widget lvo { makeWidgetAndReturnRvalueReference() };
        Widget & lvo_lvr { makeWidgetAndReturnRvalueReference() };
        Widget && lvo_rvr { makeWidgetAndReturnRvalueReference() };
    }
    f(makeWidgetAndReturnRvalueReference());
    
    return 0;
}
