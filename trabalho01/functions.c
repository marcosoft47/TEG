

for (int i = 0; i < quantLinhas; i++)
{
    for (int a = i; a < quantLinhas; a++)
    {
        if (a != i)
        {
            for (int j = 0; j < quantColunas; j++)
            {
                aux0 = aux0 + (sqrt(pow(matrizEntrada[a][j], 2)) - sqrt(pow(matrizEntrada[i][j], 2)));
            }
            if (aux0 > maiorDist){
                maiorDist = aux0;
            }
            aux0 = 0;
        }
        else
        {
            matrizSaida[i][a] = 0;
        }
    }
}