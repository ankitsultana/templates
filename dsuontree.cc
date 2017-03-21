// TODO : Compute subtree sizes
void add(int r, int p) {
  // TODO : Do something here
  for(auto &elem: adj[r]) {
    if(elem != p && !big[elem]) {
      add(elem, r);
    }
  }
}
void rem(int r, int p) {
  // TODO
  for(auto &elem: adj[r]) {
    if(elem != p && !big[elem]) {
      rem(elem, r);
    }
  }
}

void go(int r, int p, bool keep = false) {
  int bigchild = -1, maxim = 0;
  for(auto &elem: adj[r]) {
    if(elem != p && subtree[elem] > maxim) {
      maxim = subtree[elem], bigchild = elem;
    }
  }
  if(bigchild != -1) big[bigchild] = true;
  for(auto &elem: adj[r]) {
    if(elem != p && elem != bigchild) {
      go(elem, r, false);
    }
  }
  if(bigchild != -1) go(bigchild, r, true);
  add(r, p);
  // TODO : Ready
  if(bigchild != -1) big[bigchild] = false;
  if(!keep) rem(r, p);
}
