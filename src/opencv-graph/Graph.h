/* 
 * File:   Graph.h
 * Author: christian
 *
 * Created on 26. Mai 2014, 17:12
 */

#ifndef GRAPH_H
#define	GRAPH_H
#include <string>
#include <list>
#include <opencv2/opencv.hpp>
#include <mutex>

class Graph
{
public:
	/**
	 * Die Werte werden in das Bild skaliert
	 * @param minValue Minimaler Wert der Anzuzeigenden Werte
	 * @param maxValue Maximaler Wert der Anzuzeigenden Werte
	 * @param width breite des Fensters
	 * @param height höhe des Fensters
	 * @param numberOfValues Anzahl der Werte die Gespeichert werden
	 * @param imageName Fenstertitel
	 */
	Graph(int minValue,
		int maxValue,
		unsigned int width,
		unsigned int height,
		unsigned int numberOfValues,
		std::string imageName);
	std::mutex myMutex;
	/**
	 * Zeichnet das Diagramm neu
	 */
	void display();
	/**
	 * trägt die neuen Verte ein
	 * @param values Array von neuen werten
	 * @param numberOfValues anzahl der neuen Werte
	 */
	void updateValues(unsigned int* values, unsigned int numberOfValues);
	/**
	 * trägt einen neuen Wert ein
	 * danach muss display() aufgerufen werden um die Werte anzuzeigen
	 * @param value neuer Wert
	 */
	void updateValue(unsigned int value);
	/**
	 * ändert den Wertebereich der Anzeige
	 * danach muss display() aufgerufen werden um die Werte anzuzeigen
	 * @param minValue neuer Minimaler Wert
	 * @param maxValue neuer Maximaler Wert
	 */
	void setValueRange(unsigned int minValue, unsigned int maxValue);
	virtual ~Graph();
private:
	std::string imageName;
	std::list<unsigned int> values;
	void updateValuePr(unsigned nt value);

	cv::Mat* image;
	unsigned int numberOfValues;
	unsigned int minValue;
	unsigned int maxValue;

	unsigned int width;
	unsigned int heigth;

};

#endif	/* GRAPH_H */

