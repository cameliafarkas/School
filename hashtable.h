#ifndef __HASHTABLE__H
#define __HASHTABLE__H
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

    template<typename Tkey, typename Tvalue>
    struct elem_info {
        Tkey key;
        Tvalue value;
        bool recent;
        bool dirty;


        elem_info()
        {
            key = -1;
            dirty = 0;
            value = 0;
        }
    };
    template<typename Tkey, typename Tvalue>
    class set {

    public:
            elem_info<Tkey, Tvalue> *s;

            set()
            {
                s = new elem_info<Tkey, Tvalue>[2];
            }
            ~set()
            {
              delete[] s;
            }

    };

    template<typename Tkey, typename Tvalue>
    class Hashtable {
        private:
            set<Tkey, Tvalue>* H;
            int HMAX;
            int (*hash) (Tkey);

        public:

            Hashtable(int hmax, int (*h)(Tkey))
            {

                hash = h;

                H = new set<Tkey, Tvalue>[hmax];

            }

            ~Hashtable()
            {
                delete[] H;
            }

             unsigned int put(Tkey key, Tvalue value, bool write_back)
            {
                unsigned int idx, aux;

                idx = hash(key);

                 if(H[idx].s[0].key == key)
                {
                    aux = H[idx].s[0].value;
                    H[idx].s[0].value = value;

                    if(write_back)
                    {
                  
                        return aux;
                    }

                    return -1;
                }

                if(H[idx].s[1].key == key)
                {
                    aux = H[idx].s[1].value;
                    H[idx].s[1].value = value;

                    if(write_back)
                    {
                        return aux;
                    }

                    return -1;
                }


                if(H[idx].s[0].key == -1)
                {
                    H[idx].s[0].key = key;
                    H[idx].s[0].value = value;
                    H[idx].s[0].recent = 1;
                    H[idx].s[1].recent = 0;

                    return 0;
                }

                if(H[idx].s[1].key == -1)
                {
                    H[idx].s[1].key = key;
                    H[idx].s[1].value = value;
                    H[idx].s[1].recent = 1;
                    H[idx].s[0].recent = 0;

                    return -1;

                }

                if(H[idx].s[0].recent == 0)
                {
                    H[idx].s[0].key = key;
                    H[idx].s[0].value = value;
                    H[idx].s[0].recent = 1;
                    H[idx].s[1].recent = 0;

                    return -1;
                }

                if(H[idx].s[1].recent == 0)
                {
                    H[idx].s[1].key = key;
                    H[idx].s[1].value = value;
                    H[idx].s[1].recent = 1;
                    H[idx].s[0].recent = 0;

                    return -1;
                }

                return -1;

            }


            Tvalue get(Tkey key)
            {
                int idx;

                idx=hash(key);

                if((H[idx].s[0].key == key)&&(H[idx].s[0].dirty == 0))
                {
                    return H[idx].s[0].value;
                }
                if((H[idx].s[1].key == key)&&(H[idx].s[1].dirty == 0))
                {
                    return H[idx].s[1].value;
                }
            }

            bool has_key(Tkey key)
            {
                int idx;
                idx = hash(key);

                if(H[idx].s[0].key == key)
                {
                    return 1;
                }
                if(H[idx].s[1].key == key)
                {
                    return 1;
                }

                return 0;
            }

            bool is_dirty(Tkey key)
            {
                int idx;

                idx = hash(key);

                if((H[idx].s[0].key == key)&&(H[idx].s[0].dirty == 1))
                {
                    return 1;
                }
                if((H[idx].s[1].key == key)&&(H[idx].s[1].dirty == 1))
                {
                    return 1;
                }

                return 0;
            }

            void make_dirty(Tkey key) 
            {
                int idx;

                idx = hash(key);

                if(H[idx].s[0].key == key)
                {   
                    H[idx].s[0].dirty = 1;
                }
                if(H[idx].s[1].key == key)
                {

                    H[idx].s[1].dirty = 1;
                }
            
            }

            int get_key(unsigned int i, unsigned int way)
            {
                return H[i].s[way].key;
            }


    };

    #endif //__HASHTABLE__H
