int mex(vector<int> &v) {
    vector<int> vis(v.size() + 2, false);
    for(auto &elem: v) {
        if(elem < vis.size())
            vis[elem] = true;
    }
    for(int i = 0; i < vis.size(); i++)
        if(!vis[i])
            return i;
    assert(false);
    return -1;
}
