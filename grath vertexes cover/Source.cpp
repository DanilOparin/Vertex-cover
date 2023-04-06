#include<iostream>
#include<vector>
#include<thread>


struct Vertex
{
	int id;
	std::vector<int>connectionVertexes;

};


bool IsGraphEmpty(std::vector<Vertex>& Graph)
{
	for (int i_2 = 0; i_2 < Graph.size(); i_2++)
	{

		if (!Graph[i_2].connectionVertexes.empty())
		{
			return false;
		}

		if (i_2 + 1 == Graph.size())
		{
			return true;
		}

	}
}


void PrintGraph(std::vector<Vertex>& Graph)
{
	for (int i = 0; i < Graph.size(); i++)
	{
		std::cout <<Graph[i].id << " " << "вершина" << std::endl;
		std::cout << "вершины с которыми соединена " << i + 1 << " вершина" << std::endl;
		for (int i2 = 0; i2 < Graph[i].connectionVertexes.size(); i2++)
		{
			std::cout << Graph[i].connectionVertexes[i2] << " ";
		}
		std::cout << std::endl;
	}
}



void DeleteVertex(std::vector<Vertex>& graph, int number)
{
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].connectionVertexes.size(); j++)
		{

			if (graph[number].id == graph[i].connectionVertexes[j])
			{
				std::vector<int>::iterator ptr1 = graph[i].connectionVertexes.begin() + j;
				graph[i].connectionVertexes.erase(ptr1);
			}
		}
	}
	std::vector<Vertex>::iterator ptr2 = graph.begin() + number;
	graph.erase(ptr2);
	
}



void SortListVertexCover(std::vector<std::vector<int>>& listVertexCover)
{
	int count = 0;
	int minCount = listVertexCover[0].size();
	for (int i = 0; i < listVertexCover.size(); i++) {
		for (
			auto it = listVertexCover[i].begin();
			it != listVertexCover[i].end(); it++)
		{
			count++;
		}
		if (minCount > count)
		{
			minCount = count;
		}
		count = 0;
	}

	
	for (int i = 0; i < listVertexCover.size(); i++) {
		for (
			auto it = listVertexCover[i].begin();
			it != listVertexCover[i].end(); it++)
		{
			count++;
		}
		if (minCount < count)
		{
			std::vector<std::vector<int>>::iterator ptr = listVertexCover.begin() + i;
			listVertexCover.erase(ptr);
			i--;
		}
		count = 0;
	}

	int count2 = 0;
	for (int i = 0; i < listVertexCover.size(); i++) {
		for (
			auto it = listVertexCover[i].begin();
			it != listVertexCover[i].end() - 1; it++)
		{
			count2++;
			for (
				auto it2 = listVertexCover[i].begin() + count2;
				it2 != listVertexCover[i].end(); it2++)
			{
				if (*it > *it2)
				{
					count = *it2;
					*it2 = *it;
					*it = count;
				}
			}
		}
		count2 = 0;
	
	}

	for (int i = 0; i < listVertexCover.size(); i++) {
		for (int j = i + 1; j < listVertexCover.size(); j++)
		{
			
			if (listVertexCover[i] == listVertexCover[j])
			{
				std::vector<std::vector<int>>::iterator ptr = listVertexCover.begin() + j;
				listVertexCover.erase(ptr);
				j--;
			}
			
		}
		
	}
}

std::vector<std::vector<int>> FindVertexCover1(std::vector<Vertex>& Graph)
{
	std::vector<Vertex> vertexCover1;
	std::vector<Vertex> graphCopy1 = Graph;
	std::vector<std::vector<int>> listVertexCover1;
	std::vector<Vertex> resurGraph1;
	std::vector<int> copyId1;
	std::vector<Vertex> resurGraph2;
	for (int i_1 = Graph.size() / 2; i_1 < Graph.size(); i_1++)//какое число будет первым
	{
		resurGraph1 = Graph;

		vertexCover1.push_back(Graph[i_1]);
		DeleteVertex(graphCopy1, i_1);
		if (IsGraphEmpty(graphCopy1))
		{

			for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
			{
				copyId1.push_back(vertexCover1[j_1].id);
			}
			listVertexCover1.push_back(copyId1);
			copyId1.clear();
			graphCopy1 = resurGraph1;
			vertexCover1.clear();
			continue;
		}



		resurGraph1 = graphCopy1;
		for (int i_2 = 0; i_2 < graphCopy1.size(); i_2++)//по сколько чисел берем
		{
			graphCopy1 = resurGraph1;

			for (int i_8 = 0; i_8 < i_2 - 1; i_8++)
			{
				vertexCover1.push_back(graphCopy1[i_8]);
				DeleteVertex(graphCopy1, i_8);
				if (IsGraphEmpty(graphCopy1))
				{

					for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
					{
						copyId1.push_back(vertexCover1[j_1].id);
					}
					listVertexCover1.push_back(copyId1);
					copyId1.clear();
					i_2 = graphCopy1.size();
					break;

				}
			}
			resurGraph1 = graphCopy1;
			resurGraph2 = graphCopy1;
			if (i_2 >= 1)
			{
				for (int i_9 = 0; i_9 < graphCopy1.size(); i_9++)//предпоследнее число
				{
					graphCopy1 = resurGraph2;
					vertexCover1.push_back(graphCopy1[i_9]);
					DeleteVertex(graphCopy1, i_9);
					if (IsGraphEmpty(graphCopy1))
					{

						for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
						{
							copyId1.push_back(vertexCover1[j_1].id);
						}
						listVertexCover1.push_back(copyId1);
						copyId1.clear();
						graphCopy1 = resurGraph1;
						vertexCover1.pop_back();
						continue;

					}

					resurGraph1 = graphCopy1;

					for (int i_4 = i_9; i_4 < graphCopy1.size(); i_4++)//последнне число
					{


						vertexCover1.push_back(graphCopy1[i_4]);
						DeleteVertex(graphCopy1, i_4);
						if (IsGraphEmpty(graphCopy1))
						{

							for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
							{
								copyId1.push_back(vertexCover1[j_1].id);
							}
							listVertexCover1.push_back(copyId1);
							copyId1.clear();
						}

						vertexCover1.pop_back();
						graphCopy1 = resurGraph1;

					}

					vertexCover1.pop_back();
				}
			}
			else
			{
				for (int i_4 = 0; i_4 < graphCopy1.size(); i_4++)//последнне число
				{


					vertexCover1.push_back(graphCopy1[i_4]);
					DeleteVertex(graphCopy1, i_4);
					if (IsGraphEmpty(graphCopy1))
					{

						for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
						{
							copyId1.push_back(vertexCover1[j_1].id);
						}
						listVertexCover1.push_back(copyId1);
						copyId1.clear();


					}
					vertexCover1.pop_back();
					graphCopy1 = resurGraph1;
				}
			}


			resurGraph1 = resurGraph2;


		}

		graphCopy1 = Graph;
		vertexCover1.clear();
	}

	return listVertexCover1;
}

std::vector<std::vector<int>> FindVertexCover2(std::vector<Vertex>& Graph)
{
	std::vector<Vertex> vertexCover1;
	std::vector<Vertex> graphCopy1 = Graph;
	std::vector<std::vector<int>> listVertexCover1;
	std::vector<Vertex> resurGraph1;
	std::vector<int> copyId1;
	std::vector<Vertex> resurGraph2;
	for (int i_1 = 0; i_1 < Graph.size() / 2; i_1++)//какое число будет первым
	{
		resurGraph1 = Graph;

		vertexCover1.push_back(Graph[i_1]);
		DeleteVertex(graphCopy1, i_1);
		if (IsGraphEmpty(graphCopy1))
		{

			for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
			{
				copyId1.push_back(vertexCover1[j_1].id);
			}
			listVertexCover1.push_back(copyId1);
			copyId1.clear();
			graphCopy1 = resurGraph1;
			vertexCover1.clear();
			continue;
		}



		resurGraph1 = graphCopy1;
		for (int i_2 = 0; i_2 < graphCopy1.size(); i_2++)//по сколько чисел берем
		{
			graphCopy1 = resurGraph1;

			for (int i_8 = 0; i_8 < i_2 - 1; i_8++)
			{
				vertexCover1.push_back(graphCopy1[i_8]);
				DeleteVertex(graphCopy1, i_8);
				if (IsGraphEmpty(graphCopy1))
				{

					for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
					{
						copyId1.push_back(vertexCover1[j_1].id);
					}
					listVertexCover1.push_back(copyId1);
					copyId1.clear();
					i_2 = graphCopy1.size();
					break;

				}
			}
			resurGraph1 = graphCopy1;
			resurGraph2 = graphCopy1;
			if (i_2 >= 1)
			{
				for (int i_9 = 0; i_9 < graphCopy1.size(); i_9++)//предпоследнее число
				{
					graphCopy1 = resurGraph2;
					vertexCover1.push_back(graphCopy1[i_9]);
					DeleteVertex(graphCopy1, i_9);
					if (IsGraphEmpty(graphCopy1))
					{

						for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
						{
							copyId1.push_back(vertexCover1[j_1].id);
						}
						listVertexCover1.push_back(copyId1);
						copyId1.clear();
						graphCopy1 = resurGraph1;
						vertexCover1.pop_back();
						continue;

					}

					resurGraph1 = graphCopy1;

					for (int i_4 = i_9; i_4 < graphCopy1.size(); i_4++)//последнне число
					{


						vertexCover1.push_back(graphCopy1[i_4]);
						DeleteVertex(graphCopy1, i_4);
						if (IsGraphEmpty(graphCopy1))
						{

							for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
							{
								copyId1.push_back(vertexCover1[j_1].id);
							}
							listVertexCover1.push_back(copyId1);
							copyId1.clear();
						}

						vertexCover1.pop_back();
						graphCopy1 = resurGraph1;

					}

					vertexCover1.pop_back();
				}
			}
			else
			{
				for (int i_4 = 0; i_4 < graphCopy1.size(); i_4++)//последнне число
				{


					vertexCover1.push_back(graphCopy1[i_4]);
					DeleteVertex(graphCopy1, i_4);
					if (IsGraphEmpty(graphCopy1))
					{

						for (int j_1 = 0; j_1 < vertexCover1.size(); j_1++)
						{
							copyId1.push_back(vertexCover1[j_1].id);
						}
						listVertexCover1.push_back(copyId1);
						copyId1.clear();


					}
					vertexCover1.pop_back();
					graphCopy1 = resurGraph1;
				}
			}


			resurGraph1 = resurGraph2;


		}

		graphCopy1 = Graph;
		vertexCover1.clear();
	}

	return listVertexCover1;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	//„тобы создать граф нужно в начале ввести сколько будет всего вершин в графе
	//а потом дл€ каждой вершины нужно ввести сколько у нее ребер и с какими другими вершинами соединена эта вершина этими ребрами(программа запоминает с какими вершинами уже соединена ваша вершина которую вы заполн€ете)
	std::cout << "—колько вершин будет в графе?" << std::endl;
	int N;
	std::cin >> N;
	//создание графа
	std::vector<Vertex> Graph;
	for (int i = 1; i <= N; i++)
	{
		
		Vertex vertex;
		vertex.id=i;

		Graph.push_back(vertex);
	}
	
	for (int i = 0; i < Graph.size(); i++)
	{
		std::cout << "—колько ребер будет у " << i+1 << " вершины ?";
		int N2;
		std::cin >> N2;
		
		std::cout << "ID вашей вершины "<<Graph[i].id << std::endl;
		std::cout << "¬ершины с которыми она уже  соединена " <<  std::endl;
		for (int i2 = 0; i2 < Graph[i].connectionVertexes.size(); i2++)
		{
			std::cout << Graph[i].connectionVertexes[i2]<< " ";
		}
		std::cout << std::endl;
		std::cout << "—писок существующих вершин" << std::endl;
		for (int i3 = 0; i3 < Graph.size(); i3++)
		{
			std::cout << Graph[i3].id << " ";
		}
		std::cout << std::endl;
		int sizeOfConnectionVertexies = Graph[i].connectionVertexes.size();
		for (int edgeID = 1; edgeID <= N2-sizeOfConnectionVertexies; edgeID++)
		{
			std::cout << "— какой вершиной из списка выше будет соединено ваше " << edgeID << " ребро"<<std::endl;
			int idVertex;
			std::cin >> idVertex;
			Graph[i].connectionVertexes.push_back(idVertex);
			Graph[idVertex - 1].connectionVertexes.push_back(i + 1);
		}

	}

	//вывод графа
	std::cout << "¬аш граф" << std::endl;
	PrintGraph(Graph);

	//данные дл€ второго потока
	
	std::vector<std::vector<int>> listVertexCover1;
	
	//данные дл€ основного потока
	
	std::vector<std::vector<int>> listVertexCover2;
	



	std::thread secondThread([&] {


		listVertexCover1 = FindVertexCover1(Graph);

		SortListVertexCover(listVertexCover1);

	});


	
	
	
	listVertexCover2 = FindVertexCover2(Graph);
	SortListVertexCover(listVertexCover2);


	secondThread.join();

	for (int i = 0; i < listVertexCover2.size(); i++)
	{
		listVertexCover1.push_back(listVertexCover2[i]);
	}
		
	SortListVertexCover(listVertexCover1);
	std::cout << "¬ершинные покрыти€ графа:" << std::endl;
	for (int i = 0; i < listVertexCover1.size(); i++) {
		for (
			auto it = listVertexCover1[i].begin();
			it != listVertexCover1[i].end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	
	
	return 0;

}