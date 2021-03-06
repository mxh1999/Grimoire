Bool g[][]为图的邻接矩阵，图点的标号由1至n。
void dfs(int size){
	int i, j, k, t, cnt, best = 0;
	bool bb;
	if (ne[size]==ce[size]){
		if (ce[size]==0) ++ans;
		return;
	}
	for (t=0, i=1; i<=ne[size]; ++i) {
		for (cnt=0, j=ne[size]+1; j<=ce[size]; ++j)
		if (!g[list[size][i]][list[size][j]]) ++cnt;
		if (t==0 || cnt<best) t=i, best=cnt;
	}
	if (t && best<=0) return;
	for (k=ne[size]+1; k<=ce[size]; ++k) {
		if (t>0){
			for (i=k; i<=ce[size]; ++i) if (!g[list[size][t]][list[size][i]]) break;
			swap(list[size][k], list[size][i]);
		}
		i=list[size][k];
		ne[size+1]=ce[size+1]=0;
		for (j=1; j<k; ++j)if (g[i][list[size][j]]) list[size+1][++ne[size+1]]=list[size][j];
		for (ce[size+1]=ne[size+1], j=k+1; j<=ce[size]; ++j)
		if (g[i][list[size][j]]) list[size+1][++ce[size+1]]=list[size][j];
		dfs(size+1);
		++ne[size];
		--best;
		for (j=k+1, cnt=0; j<=ce[size]; ++j) if (!g[i][list[size][j]]) ++cnt;
		if (t==0 || cnt<best) t=k, best=cnt;
		if (t && best<=0) break;
	}
}
void work(){
	int i;
	ne[0]=0; ce[0]=0;
	for (i=1; i<=n; ++i) list[0][++ce[0]]=i;
	ans=0;
	dfs(0);
}
