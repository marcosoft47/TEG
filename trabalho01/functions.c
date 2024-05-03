

for (int i = 0; i < nLinhas; i++)
{
    for (int a = i; a < nLinhas; a++)
    {
        if (a != i)
        {
            for (int j = 0; j < nColunas; j++)
            {
                aux0 = aux0 + (sqrt(pow(matrizEntrada[a][j], 2)) - sqrt(pow(matrizEntrada[i][j], 2)));
            }
            if (aux0 > maiorDist)
            {
                maiorDist = aux0;
            }
            matrizSaida[i][a] = aux0;
            matrizSaida[a][i] = aux0;
            aux0 = 0;
        }
        else
        {
            matrizSaida[i][a] = 0;
        }
    }
}

for (int i = 0; i < nLinhas; i++)
{
    for (int a = 0; a < nLinhas; a++)
    {
        matrizSaida[i][a] = matrizSaida[i][a] / maiorDist;
    }
}
