#include<bits/stdc++.h>
using namespace std;

struct node{
    int left,right,par,path_par;
    node(){
        left=right=par=path_par=-1;
    }
};
class forest{
private:
    int n;
    vector<node> nodes;
    void RouteR(int v){
        int p=nodes[v].par;
        if(p==-1)
            return;
        nodes[v].path_par=nodes[p].path_par;
        nodes[p].path_par=-1;
        int pp=nodes[p].par;
        nodes[v].par=pp;
        if(pp!=-1)
            if(nodes[pp].right==p)
                nodes[pp].right=v;
            else
                nodes[pp].left=v;
        int c=nodes[v].right;
        nodes[v].right=p;
        nodes[p].left=c;
        nodes[p].par=v;
        if(c!=-1)
            nodes[c].par=p;
    }
    void RouteL(int v){
        int p=nodes[v].par;
        if(p==-1)
            return;
        nodes[v].path_par=nodes[p].path_par;
        nodes[p].path_par=-1;
        int pp=nodes[p].par;
        nodes[v].par=pp;
        if(pp!=-1)
            if(nodes[pp].left==p)
                nodes[pp].left=v;
            else
                nodes[pp].right=v;
        int c=nodes[v].left;
        nodes[v].left=p;
        nodes[p].right=c;
        nodes[p].par=v;
        if(c!=-1)
            nodes[c].par=p;
    }
    void splay(int v){
        int p=nodes[v].par;
        if(p==-1)
            return;
        int pp=nodes[p].par;
        if(pp==-1){
            if(nodes[p].left==v)
                RouteR(v);
            else
                RouteL(v);
            return;
        }
        if(nodes[pp].left==p)
            if(nodes[p].left==v){
                RouteR(p);
                RouteR(v);
            }
            else{
                RouteL(v);
                RouteR(v);
            }
        else
            if(nodes[p].right==v){
                RouteL(p);
                RouteL(v);
            }
            else{
                RouteR(v);
                RouteL(v);
            }
        splay(v);
    }
    void DetachR(int v){
        int r=nodes[v].right;
        nodes[v].right=-1;
        if(r!=-1){
            nodes[r].par=-1;
            nodes[r].path_par=v;
        }
    }
    void AtachL(int v,int w){
        nodes[v].left=w;
        nodes[w].par=v;
        nodes[w].path_par=-1;
    }
    void AtachR(int v,int w){
        nodes[v].right=w;
        nodes[w].par=v;
        nodes[w].path_par=-1;
    }
    int access(int v){
        splay(v);
        DetachR(v);
        int ans=v;
        while(nodes[v].path_par!=-1){
            int w=nodes[v].path_par;
            ans=w;
            splay(w);
            DetachR(w);
            AtachR(w,v);
            splay(v);
        }
        return ans;
    }
public:
    forest(int n) : n(n){
        nodes.resize(n+1);
    }
    int find_root(int v){
        access(v);
        while(nodes[v].left=!-1)
            v=nodes[v].left;
        return v;
    }
    void cut(int v){
        access(v);
        int p=nodes[v].left;
        if(p==-1)
            return;
        nodes[p].par=-1;
        nodes[v].left=-1;
    }
    void link(int p,int v){
        access(p);
        access(v);
        AtachL(v,p);
    }
    int lca(int v,int u){
        access(v);
        return access(u);
    }
};

int main(){
    int T,n;
    cin >> n >> T;
    forest G(n);
    while(T--){
        string st;
        cin >> st;
        if(st=="cut"){
            int v;
            cin >> v;
            G.cut(v);
        }
        if(st=="link"){
            int v,w;
            cin >> v >> w;
            G.link(w,v);
        }
        if(st=="lca"){
            int v,u;
            cin >> v >> u;
            cout << G.lca(v,u) << endl;
        }
        if(st=="root"){
            int v;
            cin >> v;
            cout << G.find_root(v) << endl;
        }
    }
}
