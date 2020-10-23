//
// Created by omkarkh1 on 12/10/20.
//

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include<ctime>
#include<unistd.h>


#define ll long long
#define f(i,x,y,inc) for(int i = x;i<y;i+=inc)
#define fl(i,x,y,inc) for(ll i = x;i<y;i+=inc)
#define w(t) int t;cin >> t;while(t--)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pls pair<ll,string>
#define inp(x) int x;cin >> x;
#define inpl(x) ll x;cin >> x;
#define vi vector<int>
#define vl vector<ll>
#define vs vector<string>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using namespace boost::multiprecision;
using namespace boost::algorithm;
using namespace std::chrono;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> new_set;

bool compare(pair<vector<int>,string>x,pair<vector<int>,string>y){
    if(x.F[2] == y.F[2] and x.F[1] == y.F[1]){
        return x.F[0] > y.F[0];
    }
    if(x.F[2] == y.F[2]){
        return x.F[1] > y.F[1];
    }
    return x.F[2] > y.F[2];
}

class PDB{
private:
    vector<vector<string> > extract_data(){
        std::ifstream input(file_name);
        vector<vector<string> >v;
        vector<string>x;
        for( std::string line;getline(input,line);){
            x.push_back(line);
        }

        for(auto y : x){
            vector<string> temp;
            vector<string> addActual;
            boost::split(temp, y, boost::is_any_of(" "));
            for(auto z:temp){
                trim(z);
                addActual.push_back(z);
            }
            v.push_back(addActual);
        }
        return v;
    }

    void removeRedundantSpaces(string &str){
        int n = str.length();
        int i = 0, j = -1;
        bool spaceFound = false;
        while (++j < n && str[j] == ' ');
        while (j < n){
            if (str[j] != ' '){
                if ((str[j] == '.' || str[j] == ',' ||
                     str[j] == '?') && i - 1 >= 0 &&
                    str[i - 1] == ' ')
                    str[i - 1] = str[j++];
                else
                    str[i++] = str[j++];
                spaceFound = false;
            }
            else if (str[j++] == ' '){
                if (!spaceFound)
                {
                    str[i++] = ' ';
                    spaceFound = true;
                }
            }
        }
        if (i <= 1)
            str.erase(str.begin() + i, str.end());
        else
            str.erase(str.begin() + i - 1, str.end());
    }

public:
    string file_name;

    PDB(string file_name){
        this->file_name = file_name;
    }

    void print_data(){
        vector<vector<string> > printer = extract_data();
        cout<<printer.size()<<endl;
        for(auto x : printer){
            for(auto y : x){
                cout<<y<<" ";
            }
            cout<<"\n";
        }
    }

    void write_to_file(string name_of_file){
        vector<vector<string> > printer = extract_data();
        ofstream fout;
        fout.open(name_of_file);
        for(auto x : printer){
            for(auto y : x){
                fout<<y<<" ";
            }
            fout<<endl;
        }
    }

    void create_txt_for_atom(string name_of_file){
        vector<vector<string> > director = extract_data();
        ofstream fout;
        fout.open(name_of_file);
        for(auto x : director){
            if(x[0].find("ATOM") != string::npos){
                for(int i = 0;i<x.size();i++){
                    trim(x[i]);
                    fout<<x[i]<<" ";
                }
                fout<<endl;
            }
        }
    }
    vector<vector<string>> read_from_atom_txt(string name_of_file){
        std::ifstream input(name_of_file);
        vector<vector<string> >v;
        vector<string>x;
        for( std::string line;getline(input,line);){
            trim(line);
            removeRedundantSpaces(line);
            trim(line);
            x.push_back(line);
        }

        for(auto y : x){
            vector<string> temp;
            vector<string> addActual;
            boost::split(temp, y, boost::is_any_of(" "));

            for(int z = 0;z<temp.size()-1;z++){
                trim(temp[z]);
                addActual.push_back(temp[z]);
            }
            v.push_back(addActual);
        }

        return v;
    }
};

class Atom{
private:
    vector<vector<float>> reader(string file_name,int xIndex = 6,int yIndex = 7,int zIndex = 8){
        std::ifstream input(file_name);
        vector<vector<string> >v;
        vector<string>x;
        //cout<<1<<endl;
        for( std::string line;getline(input,line);){
            //cout<<line<<endl;
            trim(line);
            removeRedundantSpaces(line);
            trim(line);
            x.push_back(line);
        }
//        for(auto qq:x){
//            cout<<qq<<endl;
//        }
        for(auto y : x){
            vector<string> temp;
            vector<string> addActual;
            boost::split(temp, y, boost::is_any_of(" "));

            for(int z = 0;z<temp.size()-1;z++){
                trim(temp[z]);
                removeRedundantSpaces(temp[z]);
                trim(temp[z]);
                addActual.push_back(temp[z]);
            }
            v.push_back(addActual);
        }

//        for(auto q : v){
//            cout<<q.size()<<endl;
//        }
        vector<float>resX;
        for(auto read: v){
            float val = stof(read[xIndex]);
            resX.push_back(val);
        }
        vector<float>resY;
        for(auto read: v){
            float val = stof(read[yIndex]);
            resY.push_back(val);
        }
        vector<float>resZ;
        for(auto read: v){
            float val = stof(read[zIndex]);
            resZ.push_back(val);
        }

        vector<vector<float>>sol;
        sol.push_back(resX);
        sol.push_back(resY);
        sol.push_back(resZ);

        return sol;
    }

    void removeRedundantSpaces(string &str){
        int n = str.length();
        int i = 0, j = -1;
        bool spaceFound = false;
        while (++j < n && str[j] == ' ');
        while (j < n){
            if (str[j] != ' '){
                if ((str[j] == '.' || str[j] == ',' ||
                     str[j] == '?') && i - 1 >= 0 &&
                    str[i - 1] == ' ')
                    str[i - 1] = str[j++];
                else
                    str[i++] = str[j++];
                spaceFound = false;
            }
            else if (str[j++] == ' '){
                if (!spaceFound)
                {
                    str[i++] = ' ';
                    spaceFound = true;
                }
            }
        }
        if (i <= 1)
            str.erase(str.begin() + i, str.end());
        else
            str.erase(str.begin() + i - 1, str.end());
    }

public:
    string  name;
    //string file_name;
    Atom(string name){
        this->name = name;
        //this->file_name = file_name;
    }

    vector<float> getAllXcoordinates(string file_name){
        vector<float> v = reader(file_name)[0];
        return v;
    }

    vector<float> getAllYcoordinates(string file_name){
        vector<float> v = reader(file_name)[1];
        return v;
    }

    vector<float> getAllZcoordinates(string file_name){
        vector<float> v = reader(file_name)[2];
        return v;
    }

    float getMinElement(vector<float> v){
        return *min_element(v.begin(),v.end());
    }

    float getMaxElement(vector<float> v){
        return *max_element(v.begin(),v.end());
    }

    vi getDimensions(vector<float>x,vector<float>y,vector<float>z){
        vi res(3);
        float xMin = getMinElement(x);
        float xMax = getMaxElement(x);
        float yMin = getMinElement(y);
        float yMax = getMaxElement(y);
        float zMin = getMinElement(z);
        float zMax = getMaxElement(z);

        int resx = ceil(xMax - xMin);
        int resy = ceil(yMax - yMin);
        int resz = ceil(zMax - zMin);

        res[0] = resx;
        res[1] = resy;
        res[2] = resz;
        sort(res.begin(),res.end());

        return res;
    }
};

class Algorithm{
public:
    int L,W,H;
    Algorithm(int L,int W,int H){
        this->L = L;
        this->W = W;
        this->H = H;
        init();
    }
    int max(int a,int b){
        if(a > b)return a;
        return b;
    }
    int max(int a,int b,int c){
        return max(c,max(a,b));
    }

    int min(int a,int b){
        if(a < b)return a;
        return b;
    }

    int min(int a,int b,int c){
        return min(a,min(b,c));
    }

    void init(){
        int t1 = max(L,W,H);
        int t3 = min(L,W,H);
        int t2 = L+W+H - t1 - t3;
        L = t3;
        W = t2;
        H = t1;
    }

    //Think about the reverse function as well.
    void reverseCuboid(vector< vector< vector<int> > > &dp,int sx,int sy,int ex,int ey,int sh,int eh){
        for(int i = sx;i<=ex/2;i++){
            for(int j = sy;j<=ey/2;j++){
                for(int k = sh;k<=eh;k++){
                    swap(dp[i][j][k],dp[j][i][k]);
                }
            }
        }
    }

    vector<pair<int,pair<int,int> > >locateonZ(vector<vector<vi>> dp,int l,int w,int h){
        vector<pair<int,pair<int,int> > > res;

        int lx = 0,ly = 0,lz = 0;
        for(int i = 0;i<L;i++){
            for(int j = 0;j<W;j++){
                for(int k = 0;k<H;k++){
                    if(dp[i][j][k] == 0){
                        pair<int,pair<int,int>> temp;
                        //temp.first = i;
                        lx++;
                        ly++;
                        lz++;
                        temp.first = i;
                        temp.second.first = j;
                        temp.second.second = k;
                        res.push_back(temp);
                        if(lx == l and ly == w and lz == h){
                            return res;
                        }
//                        else{
//                            res.clear();
//                        }
                    }
                    else{
                        res.clear();
                    }
                }
            }
        }
        return res;
    }

    vector<pair<int,pair<int,int> > >locateonY(vector<vector<vi>> dp,int l,int w,int h){
        vector<pair<int,pair<int,int> > > res;

        int lx = 0,ly = 0,lz = 0;
        for(int i = 0;i<H;i++){
            for(int j = 0;j<W;j++){
                for(int k = 0;k<L;k++){
                    if(dp[i][j][k] == 0){
                        pair<int,pair<int,int>> temp;
                        //temp.first = i;
                        lx++;
                        ly++;
                        lz++;
                        temp.first = i;
                        temp.second.first = j;
                        temp.second.second = k;
                        res.push_back(temp);
                        if(lx == l and ly == w and lz == h){
                            return res;
                        }
//                        else{
//                            res.clear();
//                        }
                    }
                    else{
                        res.clear();
                    }
                }
            }
        }
        return res;
    }

    vector<pair<int,pair<int,int> > >locateonX(vector<vector<vi>> dp,int l,int w,int h){
        vector<pair<int,pair<int,int> > > res;

        int lx = 0,ly = 0,lz = 0;
        for(int i = 0;i<L;i++){
            for(int j = 0;j<H;j++){
                for(int k = 0;k<W;k++){
                    if(dp[i][j][k] == 0){
                        pair<int,pair<int,int>> temp;
                        //temp.first = i;
                        lx++;
                        ly++;
                        lz++;
                        temp.first = i;
                        temp.second.first = j;
                        temp.second.second = k;
                        res.push_back(temp);
                        if(lx == l and ly == w and lz == h){
                            return res;
                        }
//                        else{
//                            res.clear();
//                        }
                    }
                    else{
                        lx = 0;
                        ly = 0;
                        lz = 0;
                        res.clear();
                    }
                }
            }
        }
        vector<pair<int,pair<int,int> > > pp;
        if(lx == l and ly == w and lz == h)
            return res;
        return pp;
    }

    void reset(vector<vi>&visxy){
        for(int i = 0;i<L;i++){
            for(int j = 0;j<W;j++){
                visxy[i][j] = 0;
            }
        }
    }

    void putValue(vector<vector<vi> > &dp,vector<pair<int,pair<int,int> > > p,int count,unordered_map<string,int>&mapper,vs names,int i){
        for(auto x : p){
            dp[x.first][x.second.first][x.second.second] = count;
            mapper[names[i]] = count;
        }
    }

    void dynamicDistanceUtil(vector<vector<int> >a,vector< vector< vector<int> > > &dp,int h,int w, int l,vi &visited,int count,vi &visitedl,vi &visitedw,vi &visitedh,vector<vi>&visxy,vs names,unordered_map<string,int>&mapper){
        //Figure out the base case.
        int flag = 1;
        int sign = -1;
        unordered_set<int> counter;
        int dh = 0;
        //unordered_map<string,int> mapper;
        //string names[a.size()];
        while(flag){
            sign = sign * (-1);
            flag = 1;
            if(h > H){
                break;
            }

            reset(visxy);
            for(int i =0;i<a.size();i++){
                if(visited[i] == 0){
                    flag = 0;
                }
            }

            int mh = INT_MIN;
            int templ = l;
            int tempw = w;
           // cout<<a.size()<<endl;

            // First For Loop

            for(int i = 0;i<a.size();i++){
                count++;
                if(i!=0 and a[i][0] == a[i-1][0] and a[i][1] == a[i-1][1] and a[i][2] == a[i-1][2] and visited[i-1] == 0){
                    continue;
                }
                if(visited[i] == 1){
                    continue;
                }
                if(l + a[i][0] < L and w + a[i][1] < W){
                    for(int j = l;j<a[i][0] + l;j++){
                        if( l >= L){
                            break;
                        }
                        if(visitedl[j] == 0 or visitedl[j] == 1){
                            visitedl[j] = 1;
                            for(int k = w;k<a[i][1] + w;k++){
                                if(k >= W){
                                    break;
                                }

                                if(visitedw[k] == 0 or visitedw[k] == 1){
                                    visitedw[k] = 1;
                                    for(int b = h;b<a[i][2] + h;b++){
                                        mapper[names[i]] = count;
                                        mh = max(mh,a[i][2]);
                                        visitedl[j] = 1;
                                        visitedw[k] = 1;
                                        visitedh[b] = 1;
                                        visxy[j][k] = 1;
                                        dp[j][k][b] = count;
                                        counter.insert(count);
                                    }
                                }

                            }
                        }

                    }
                    count++;
                    visited[i] = 1;
                }
                l += a[i][0];
                w += a[i][1];
                l++;
                w++;

            }

            l = templ;
            w = tempw;

            // Second for loop.
            for(int i = 0;i<a.size();i++){
                count++;
                if(i!=0 and a[i][0] == a[i-1][0] and a[i][1] == a[i-1][1] and a[i][2] == a[i-1][2] and visited[i-1] == 0){
                    continue;
                }
                if(visited[i] == 1){
                    continue;
                }


                if(l + a[i][0] < L and w + a[i][1] < W){
                    for(int j = w;j<a[i][1] + w;j++){

                        if( w >= W){
                            break;
                        }
                        if(visitedw[j] == 0 or visitedw[j] == 1){
                            visitedw[j] = 1;
                            for(int k = l;k<a[i][0] + l;k++){
                                if(visxy[k][j] == 1)
                                {
                                    if(k < L - 1 and w < L - 1){
                                        l++;
                                    }
                                    continue;
                                }
                                else{
                                    visxy[j][k] = 1;
                                }
                                if(k >= W){
                                    break;
                                }

                                if(visitedl[k] == 0 or visitedl[k] == 1){
                                    visitedl[k] = 1;
                                    for(int b = h;b<a[i][2] + h;b++){
                                        mapper[names[i]] = count;
                                        visitedl[k] = 1;
                                        visitedw[j] = 1;
                                        visitedh[b] = 1;
                                        dp[k][j][b] = count;
                                        counter.insert(count);
                                    }
                                }

                            }
                        }

                    }
                    count++;
                    visited[i] = 1;
                }
                l += a[i][0];
                l++;
                w++;

            }

            l = templ;
            w = tempw;

            // Third for loop.
            for(int i = 0;i<a.size();i++){
                count++;
                if(i!=0 and a[i][0] == a[i-1][0] and a[i][1] == a[i-1][1] and a[i][2] == a[i-1][2] and visited[i-1] == 0){
                    continue;
                }
                if(visited[i] == 1){
                    continue;
                }
                if(l + a[i][0] < L and w + a[i][1] < W){
                    for(int j = l;j<a[i][0] + l;j++){
                        if( l >= L){
                            break;
                        }
                        if(visitedl[j] == 0 or visitedl[j] == 1){
                            visitedl[j] = 1;
                            for(int k = w;k<a[i][1] + w;k++){

                                if(visxy[j][k] == 1)
                                {
                                    if(k < W - 1 and w < W - 1){
                                        k++;
                                        w++;
                                    }
                                    continue;
                                }
                                else{
                                    visxy[j][k] = 1;
                                }

                                if(k >= W){
                                    break;
                                }

                                if(visitedw[k] == 0 or visitedw[k] == 1){
                                    visitedw[k] = 1;
                                    for(int b = h;b<a[i][2] + h;b++){
                                        visitedl[j] = 1;
                                        visitedw[k] = 1;
                                        visitedh[b] = 1;
                                        mapper[names[i]] = count;
                                        dp[j][k][b] = count;
                                        counter.insert(count);
                                    }
                                }

                            }
                        }

                    }
                    count++;
                    visited[i] = 1;
                }
                w += a[i][1];
                l++;
                w++;

            }

            if(sign == -1){
                reverseCuboid(dp,0,0,L,W,h,h + mh);
            }

            h += mh;



        }

        for(auto x : counter){
            //cout<<x<<endl;
        }
        // Try for brute force approach;
        int n = a.size();
        for(int i = 0;i < n;i++){
            if(visited[i] == 0){
                vector<pair<int,pair<int,int> >> px = locateonX(dp,a[i][0],a[i][1],a[i][2]);
                if(px.size() != 0){
                    count++;
                    putValue(dp,px,count,mapper,names,i);
                    counter.insert(count);
                    visited[i] = 1;
                    continue;
                }
            if(visited[i] == 1)
                continue;
                vector<pair<int,pair<int,int> >> py = locateonY(dp,a[i][0],a[i][1],a[i][2]);
                if(py.size() != 0){
                    count++;
                    putValue(dp,py,count,mapper,names,i);
                    counter.insert(count);
                    visited[i] = 1;
                    continue;
                }
            if(visited[i] == 1)
                continue;
                vector<pair<int,pair<int,int> >> pz = locateonZ(dp,a[i][0],a[i][1],a[i][2]);
                if(pz.size() != 0){
                    count++;
                    putValue(dp,pz,count,mapper,names,i);
                    counter.insert(count);
                    visited[i] = 1;
                    continue;
                }


            }
        }

        //Write down the recursive case.
       //dynamicDistanceUtil(a,dp,h,0,0,visited,count,visitedl,visitedw,visitedh);
    }

    void removeRedundantSpaces(string &str){
        int n = str.length();
        int i = 0, j = -1;
        bool spaceFound = false;
        while (++j < n && str[j] == ' ');
        while (j < n){
            if (str[j] != ' '){
                if ((str[j] == '.' || str[j] == ',' ||
                     str[j] == '?') && i - 1 >= 0 &&
                    str[i - 1] == ' ')
                    str[i - 1] = str[j++];
                else
                    str[i++] = str[j++];
                spaceFound = false;
            }
            else if (str[j++] == ' '){
                if (!spaceFound)
                {
                    str[i++] = ' ';
                    spaceFound = true;
                }
            }
        }
        if (i <= 1)
            str.erase(str.begin() + i, str.end());
        else
            str.erase(str.begin() + i - 1, str.end());
    }


    void generatePdb(vector<vector<vector<int>>> dp, string filename, int count) {
//        unordered_set<string>delims;
//        delims.insert(" ");
//        delims.insert("  ");
//        delims.insert("   ");
//        delims.insert("    ");
//        delims.insert("     ");
//        delims.insert("      ");
//        delims.insert("       ");
//        delims.insert("        ");
//        delims.insert("         ");
//        delims.insert("          ");
//        delims.insert("           ");
//        delims.insert("            ");
        string temp = filename;
        string originalFile = filename + ".pdb";
        string randomString;
        int length = 4;
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        srand( (unsigned) time(NULL) * getpid());

        for (int i = 0; i < length; ++i)
            randomString += alphanum[rand() % (sizeof(alphanum) - 1)];
        temp+= randomString;
        temp += ".pdb";
        std::ifstream  input(originalFile);
        vector<string> x;
        int tX = L;
        int tY = W;
        int tZ = H;

        int lmin = INT_MAX;
        int wmin = INT_MAX;
        int hmin = INT_MAX;

        for(int a = 0;a<=tX;a++){
            for(int b = 0;b<=tY;b++){
                for(int c = 0;c<=tZ;c++){
                    if(dp[a][b][c] == count){
                        lmin = min(lmin,a);
                        wmin = min(wmin,b);
                        hmin = min(hmin,c);
                    }
                }
            }
        }

        for( std::string line;getline(input,line);){
            if(line.find("ATOM   ") != std::string::npos and line.find("REMARK") == std::string::npos){
                removeRedundantSpaces(line);
                vector<string>taker;
                boost::split(taker, line, boost::is_any_of(" "));
//                trim(taker[6]);
//                trim(taker[7]);
//                trim(taker[8]);
                for(int ii = 0;ii<taker.size();ii++){
                    trim(taker[ii]);
                }
                cout<<taker.size()<<endl;
                for(int ii = 0;ii<taker.size();ii++){
                    cout<<taker[ii]<<endl;
                }
                cout<<taker[6]<<taker[7]<<taker[8]<<endl;

                string xx = taker[6];
                float xxx = stof(xx);
                xxx += lmin;
                xxx -= 100;
                string tx = to_string(xxx);
                string txx(tx.begin(),tx.end()-3);
                taker[6] = txx;
                string yy = taker[7];
                float yyy = stof(yy);
                yyy += wmin;
                yyy -= 100;
                string ty = to_string(yyy);
                string tyy(ty.begin(),ty.end()-3);
                taker[7] = tyy;
                string zz = taker[8];
                float zzz = stof(zz);
                zzz += hmin;
                zzz -= 100;
                string tz = to_string(zzz);
                string tzz(tz.begin(),tz.end()-3);
                taker[8] = tzz;
                //cout<<"True"<<endl;
                string resultant;
                string t1 = taker[0];
                string t2 = "       ";
                t2.replace(t2.end()-taker[1].size(),t2.end(),taker[1]);
                string t2point5 = "  ";
                string t3 = "   ";
                t3.replace(t3.begin() ,t3.begin() + taker[2].size(),taker[2]);
                //string t3point5 = " ";
                string t4 = " ";
                t4.replace(t4.end(),t4.end() - taker[3].size(),taker[3]);
                string t5 = "  ";
                t5.replace(t5.end() - taker[4].size(),t5.end(),taker[4]);
                string t6 = "    ";
                t6.replace(t6.end() - taker[5].size(),t6.end(),taker[5]);
                string t7 = "            ";
                t7.replace(t7.end() - taker[6].size(),t7.end(),taker[6]);
                string t8 = "        ";
                t8.replace(t8.end() - taker[7].size(),t8.end(),taker[7]);
                string t9 = "        ";
                t9.replace(t9.end() - taker[8].size(),t9.end(),taker[8]);
                string t10 = "      ";
                t10.replace(t10.end() - taker[9].size(),t10.end(),taker[9]);
                string t11 = "      ";
                t11.replace(t11.end() - taker[10].size(),t11.end(),taker[10]);
                string t12 = "            ";
                t12.replace(t12.end() - taker[11].size(),t12.end(),taker[11]);
                resultant += t1+t2+t2point5+t3+t4+t5+t6+t7+t8+t9+t10+t11+t12;
                x.push_back(resultant);
            }
            else{
                x.push_back(line);
            }

        }
        ofstream fout;
        fout << std::fixed << std::setprecision(3);
        fout.open(temp);
        for(auto liner:x){
            fout<<liner<<endl;
        }

    }

    void dynamicDistance(vector<pair<vi,string>>a){
        int tX = L;
        int tY = W;
        int tZ = H;
        int n = a.size();
        vector<int> visited(n,0);
        vector<int> visitedw(W+1,0);
        vector<int> visitedl(L+1,0);
        vector<int> visitedh(H+1,0);
        vector<vector<int> >visxy(L+1,vector<int>(W+1));
        for(int i = 0;i<L;i++){
            for(int j = 0;j<W;j++){
                visxy[i][j] = 0;
            }
        }
        vector< vector< vector<int> > > dp((tX+1) , vector< vector<int> >((tY+1), vector<int> (tZ+1)));
        for(int i = 0;i<=tX;i++){
            for(int j = 0;j<=tY;j++){
                for(int k = 0;k<=tZ;k++){
                    dp[i][j][k] = 0;
                }
            }
        }
        sort(a.begin(),a.end(),compare);
        int count = 1;
        vector<vi>p;
        for(int i = 0;i<a.size();i++){
            p.push_back(a[i].F);
        }
        vector<string> names;
        for(int i = 0;i<a.size();i++){
            names.push_back(a[i].S);
        }
        unordered_map<string,int> mapper;
       dynamicDistanceUtil(p,dp,0,0,0,visited,count,visitedl,visitedw,visitedh,visxy,names,mapper);
       // unordered_set<int> s;
//        for(int i = 0;i<=tX;i++){
//            for(int j = 0;j<=tY;j++){
//                for(int k = 0;k<=tZ;k++){
//                    //cout << dp[i][j][k] << " ";
//                    if(dp[i][j][k] != 0){
//                        s.insert(dp[i][j][k]);
//                    }
//                }
//                cout<<"\n";
//            }
//            cout<<endl;
//            cout<<endl;
//        }
        vector<pair<pair<int,int>,pair<int,int>>>cd;
        for(int i = 0;i<=tX;i++){
            for(int j = 0;j<=tY;j++){
                for(int k = 0;k<=tZ;k++){
                    //cout << dp[i][j][k] << " ";
                    if(dp[i][j][k] != 0){
                        pair<pair<int,int>,pair<int,int>> temp = {{i,j},{k,dp[i][j][k]}};
                        cd.push_back(temp);
                    }
                }
                //cout<<"\n";
            }
        }
        for(auto x : cd){
            pair<int,int>xy = x.first;
            pair<int,int>zv = x.second;
            //cout<<xy.first<<" "<<xy.second<<" "<<zv.first<<" "<<zv.second<<endl;
        }
        for(int i = 0;i<visited.size();i++){
           //cout<<visited[i]<<endl;
        }

        for(auto mapx : mapper){
            generatePdb(dp,mapx.first,mapx.second);
        }
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    PDB d1("/home/omkarkh1/CLionProjects/pdb/2csn.pdb");
    PDB d2("/home/omkarkh1/CLionProjects/pdb/1pa9.pdb");
    PDB d3("/home/omkarkh1/CLionProjects/pdb/1e2s.pdb");
    PDB d4("/home/omkarkh1/CLionProjects/pdb/2csn.pdb");
    PDB d5("/home/omkarkh1/CLionProjects/pdb/1pa9.pdb");
    PDB d6("/home/omkarkh1/CLionProjects/pdb/1e2s.pdb");

    d1.write_to_file("/home/omkarkh1/CLionProjects/pdb/d1.txt");
    d1.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a1.txt");
    d2.write_to_file("/home/omkarkh1/CLionProjects/pdb/d2.txt");
    d2.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a2.txt");
    d3.write_to_file("/home/omkarkh1/CLionProjects/pdb/d3.txt");
    d3.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a3.txt");
    d4.write_to_file("/home/omkarkh1/CLionProjects/pdb/d4.txt");
    d4.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a4.txt");
    d5.write_to_file("/home/omkarkh1/CLionProjects/pdb/d5.txt");
    d5.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a5.txt");
    d6.write_to_file("/home/omkarkh1/CLionProjects/pdb/d6.txt");
    d6.create_txt_for_atom("/home/omkarkh1/CLionProjects/pdb/a6.txt");

    Atom a1("a1");
    Atom a2("a2");
    Atom a3("a3");
    Atom a4("a4");
    Atom a5("a5");
    Atom a6("a6");

    vector<float> xa1 = a1.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a1.txt");
    vector<float> ya1 = a1.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a1.txt");
    vector<float> za1 = a1.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a1.txt");

    vector<float> xa2 = a2.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a2.txt");
    vector<float> ya2 = a2.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a2.txt");
    vector<float> za2 = a2.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a2.txt");

    vector<float> xa3 = a3.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a3.txt");
    vector<float> ya3 = a3.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a3.txt");
    vector<float> za3 = a3.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a3.txt");

    vector<float> xa4 = a4.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a4.txt");
    vector<float> ya4 = a4.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a4.txt");
    vector<float> za4 = a4.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a4.txt");

    vector<float> xa5 = a5.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a5.txt");
    vector<float> ya5 = a5.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a5.txt");
    vector<float> za5 = a5.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a5.txt");

    vector<float> xa6 = a6.getAllXcoordinates("/home/omkarkh1/CLionProjects/pdb/a6.txt");
    vector<float> ya6 = a6.getAllYcoordinates("/home/omkarkh1/CLionProjects/pdb/a6.txt");
    vector<float> za6 = a6.getAllZcoordinates("/home/omkarkh1/CLionProjects/pdb/a6.txt");

    vi dim1 = a1.getDimensions(xa1,ya1,za1);
    vi dim2 = a2.getDimensions(xa2,ya2,za2);
    vi dim3 = a3.getDimensions(xa3,ya3,za3);
    vi dim4 = a4.getDimensions(xa4,ya4,za4);
    vi dim5 = a5.getDimensions(xa5,ya5,za5);
    vi dim6 = a6.getDimensions(xa6,ya6,za6);

//    cout<<dim1[0]<<" "<<dim1[1]<<" "<<dim1[2]<<endl;
//    cout<<dim2[0]<<" "<<dim2[1]<<" "<<dim2[2]<<endl;
//    cout<<dim3[0]<<" "<<dim3[1]<<" "<<dim3[2]<<endl;
//    cout<<dim4[0]<<" "<<dim4[1]<<" "<<dim4[2]<<endl;
//    cout<<dim5[0]<<" "<<dim5[1]<<" "<<dim5[2]<<endl;
//    cout<<dim6[0]<<" "<<dim6[1]<<" "<<dim6[2]<<endl;

    Algorithm algorithm(150,150,150);
    //cout<<algorithm.L << " "<<algorithm.W << " "<<algorithm.H <<endl;

    vector<pair<vi,string>>a;

    a.push_back({dim1,"2csn"});
    a.push_back({dim2,"1pa9"});
    a.push_back({dim3,"1e2s"});
//    a.push_back(dim4);
//    a.push_back(dim5);
//    a.push_back(dim6);
    auto start = high_resolution_clock::now();
    algorithm.dynamicDistance(a);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}

