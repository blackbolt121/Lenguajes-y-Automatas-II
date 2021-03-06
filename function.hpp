#pragma once
#include "estructura.hpp"
#include "iostream"
#include <map>
class funct : public estructura{
    public:
        funct(){
            declared = false;
            narg = 0;
        }
        static funct process(queue<palabra> q){
            funct foo;
            int cont = 0;
            palabra auxt;
            while(!q.empty()){
                palabra aux = q.front();
                switch(aux){
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                        if(cont == 0){
                            foo.setType(aux);
                        }else{
                            auxt = aux;
                        }
                        break;
                    case 27: //Para en caso de que se encuentre tipos varn
                    case 28:
                    case 29:
                    case 30:

                        break;
                    case 41:
                        foo.setBloque(aux.getBloque());
                        foo.setDelared();
                        break;
                    case 38:
                    case 39://En cuanto se encuentre un parentesis, debe ignorar las palabras
                        break;
                    case 31:
                        if(cont == 0){
                            foo.setNombre(aux);
                            foo.setPalabraClave(aux);
                            cont++;
                        }else{
                            if(!foo.isInArgumentes(aux)){
                                foo.incArg();
                                foo.addArgument(auxt, aux);
                            }
                            else{
                                foo.setHasError(true);
                            }
                        }
                        break;
                    case 46:
                        return foo;
                        break;
                    default:
                        break;
                }
                q.pop();
            }
            return foo;
        }
        void setType(palabra type){
            this->type = type;
        }
        void setNombre(palabra nombre){
            this->nombre = nombre;
        }
        void addArgument(palabra type, palabra var){
            this->arguments[var.getWord()] = type;
        }
        void setReturn(palabra retur){
            this->retur = retur;
        }
        void setBloque(int bloque){
            this->bloque = bloque;
        }
        void setDelared(){
            this->declared = true;
        }
        bool isInArgumentes(palabra p){
            for(pair<string,palabra> aux : arguments){
                if(aux.first.compare(p.getWord().c_str()) == 0){
                    return true;
                }       
            }
            return false;
        }
        palabra getNombre() { return this->nombre;}
        palabra getType() { return type;}
        map<string,palabra> getArguments() { return arguments; } ;
        palabra getPalabra() { return estructura::getPalabra(); }
        int getNArg() { return narg; }
        void incArg() { narg++;}
        bool isDeclared() { return declared;}
    private:
        int narg;
        palabra type;
        palabra nombre;
        map<string, palabra> arguments;
        palabra retur;
        int bloque;
        bool declared;
};