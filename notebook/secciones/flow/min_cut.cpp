//Suponemos un grafo con el formato definido en Edmond Karp o Push relabel
bitset<MAX_V> type,used; //reset this
void dfs1(int nodo)
{
	type.set(nodo);
	forall(it,G[nodo]) if(!type[it->fst] && it->snd>0) dfs1(it->fst);
}
void dfs2(int nodo)
{
	used.set(nodo);
	forall(it,G[nodo])
	{
		if(!type[it->fst])
		{
			//edge nodo -> (it->fst) pertenece al min_cut
			//y su peso original era: it->snd + G[it->fst][nodo]
			//si no existia arista original al rev�s
		}
		else if(!used[it->fst]) dfs2(it->fst);
	}
}
void minCut() //antes correr alg�n maxflow()
{
	dfs1(SRC);
	dfs2(SRC);
	return;
}
