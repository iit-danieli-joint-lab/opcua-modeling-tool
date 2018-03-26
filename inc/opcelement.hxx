#ifndef OPCELEMENT_H
#define OPCELEMENT_H

template <class T>
class OPCElement{
    public:
        OPCElement(T *opcElement): m_OPCElement(opcElement)
        {
            //Explicitly empty
        }
        OPCElement(): m_OPCElement(0)
        {
            //Explicitly empty
        }
        T* operator->()
        {
            return m_OPCElement;
        }

        T* operator*()
        {
            return m_OPCElement;
        }

    private:
        T *m_OPCElement;
};


#endif // OPCELEMENT_H
