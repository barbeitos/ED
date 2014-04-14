class Paises{
private:
  set<Pais> datos;
  
public:
  Paises();
  void Insertar(oncst Pais * p);
  void Borrar(const Pais * p);
  class const_iterator;
  
  clase iterator{
  private:
    set<Pais>::iterator p;
    
  public:
    iterator();
    bool operator==
    bool operator!=
    const Pais & operator*
    iterator begin()
    iterator end()
    iterator find()
    friend istream
    friend ostream
  };
};