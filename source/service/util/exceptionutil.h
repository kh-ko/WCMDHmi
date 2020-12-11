#ifndef EXCEPTIONDEF_H
#define EXCEPTIONDEF_H

#define CHECK_PTR_RETURN(x) if(x==nullptr){return;}
#define CHECK_PTR_BREAK(x) if(x==nullptr){break;}
#define CHECK_FALSE_RETURN(x) if(x==false){return;}
#define CHECK_FALSE_BREAK(x) if(x==false){break;}
#define CHECK_SENDER_RETURN if(sender() == nullptr)return
#endif // EXCEPTIONDEF_H
