


// edution ax + by = c ;
// given a , b , c 
// find any value of x , y ;
// or say this not exsit

// if solve_lde return >= 1 then exist solution otherwise not exsit.



void nxt(long long&a,long long&b,const long long q){
    long long t=a-q*b;
    a=b;
    b=t;
}
long long egcd(long long r0,long long r1,long long&x0,long long&y0){
    long long y1=x0=1;
    long long x1=y0=0;
    while(r1){
        long long q=r0/r1;
        nxt(r0,r1,q);
        nxt(x0,x1,q);
        nxt(y0,y1,q);
    }
    return r0;
}
bool solve_lde(long long a,long long b,long long c,long long&x,long long&y,long long&g){
    g=egcd(a,b,x,y);
    long long m=c/g;
    x*=m;
    y*=m;
    return !(c%g);
}