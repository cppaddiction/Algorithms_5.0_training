#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

class Entity;

bool prev_was_sur = false;
bool prev_was_floating = false;
bool jump = false;

set<int> surrounded_ys;
map<int, pair<int, Entity>> surrounded_images;

pair<int, int> last_pasted_coords;
vector<pair<int, int>> floating_images;

vector<pair<int, int>> answer;

vector<string> Split(const string& str)
{
	int i = 0;
	string s;
	vector<string> result;
	while (i < str.size())
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r' && str[i] != '\f' && str[i] != '\v')
		{
			s += str[i];
		}
		else
		{
			if (s != "")
			{
				result.push_back(s);
			}
			s = "";
		}
		i++;
	}
	if (s != "")
	{
		result.push_back(s);
	}
	return result;
}

std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

int ExtractValue(const string& s, char& c, int& i)
{
	string str;

	c = s[++i];

	while (c != ' ' && c != ')') { str += c; c = s[++i]; }

	return stoi(str);
}

string ExtractString(const string& s, char& c, int& i)
{
	string str;

	c = s[++i];

	while (c != ' ' && c != ')') { str += c; c = s[++i]; }

	return str;
}

class Entity {
public:
	Entity() = default;
	explicit Entity(int dx, int dy, int w, int h, string type, string info = "") : dx_(dx), dy_(dy), w_(w), h_(h), type_(type), info_(info) {}
	int GetDx() const { return dx_; }
	int GetDy() const { return dy_; }
	int GetWidth() const { return w_; }
	int GetHeight() const { return h_; }
	const string& GetType() const { return type_; }
	const string& GetInfo() const { return info_; }
private:
	int dx_ = 0;
	int dy_ = 0;
	int w_ = 0;
	int h_ = 0;
	string type_ = "";
	string info_ = "";
};

class Cursor {
public:
	explicit Cursor(int x, int y, int w, int h, int h_current, int c) : x_(x), y_(y), w_(w), h_(h), h_current_(h_current), c_(c) {}
	void Paste(const vector<Entity>& v)
	{
		if (v.size() == 0)
		{
			if (surrounded_ys.size() > 0)
			{
				if (y_ + h_current_ > *next(surrounded_ys.end(), -1))
				{
					Newline();
				}
				else
				{
					x_ = 0;
					y_ = *next(surrounded_ys.end(), -1);
					h_current_ = h_;
				}
			}
			else
			{
				Newline();
			}
			prev_was_sur = false;
			prev_was_floating = false;
			jump = false;
		}
		else
		{
			vector<pair<int, int>> bounds = GetBoundaries();
			for (const auto& entity : v)
			{
				if (entity.GetType() == "text")
				{
					int i = 0;
					string txt = entity.GetInfo();
					vector<string> words = Split(txt);
					while (i < words.size())
					{
						for (int k = 0; k < bounds.size(); k++)
						{
							if (x_ < bounds[k].first) { x_ = bounds[k].first; }
							while (i < words.size() && bounds[k].first <= x_ && x_ < bounds[k].second)
							{
								if (x_ == bounds[k].first)
								{
									if (x_ + words[i].size() * c_ <= bounds[k].second)
									{
										jump = false;
										x_ += (words[i].size() * c_);
										i++;
										prev_was_sur = false;
										if (x_ == bounds[k].second)
										{
											if (k == bounds.size() - 1)
											{
												jump = false;
												x_ = bounds[k].second;
											}
											else
											{
												jump = true;
												last_pasted_coords = make_pair(x_, y_);
												x_ = bounds[k + 1].first;
											}
										}
									}
									else
									{
										prev_was_sur = false;
										if (k == bounds.size() - 1)
										{
											jump = false;
											x_ = bounds[k].second;
										}
										else
										{
											jump = true;
											last_pasted_coords = make_pair(x_, y_);
											x_ = bounds[k + 1].first;
										}
									}
								}
								else
								{
									if (prev_was_sur)
									{
										if (x_ + words[i].size() * c_ <= bounds[k].second)
										{
											jump = false;
											x_ += (words[i].size() * c_);
											i++;
											prev_was_sur = false;
										}
										else
										{
											if (k == bounds.size() - 1)
											{
												jump = false;
												x_ = bounds[k].second;
											}
											else
											{
												jump = true;
												last_pasted_coords = make_pair(x_, y_);
												x_ = bounds[k + 1].first;
											}
										}
									}
									else
									{
										prev_was_sur = false;
										if (x_ + c_ + words[i].size() * c_ <= bounds[k].second)
										{
											jump = false;
											x_ += (c_ + words[i].size() * c_);
											i++;
											prev_was_sur = false;
										}
										else
										{
											if (k == bounds.size() - 1)
											{
												jump = false;
												x_ = bounds[k].second;
											}
											else
											{
												jump = true;
												last_pasted_coords = make_pair(x_, y_);
												x_ = bounds[k + 1].first;
											}
										}
									}
								}
							}
							if (!(i < words.size()))
							{
								break;
							}
						}
						if (i < words.size())
						{
							Newline();
							bounds = GetBoundaries();
						}
					}
					prev_was_floating = false;
				}
				else if (entity.GetType() == "embedded" || entity.GetType() == "surrounded")
				{
					bool paste = false;
					while (!paste)
					{
						for (int i = 0; i < bounds.size(); i++)
						{
							if (x_ < bounds[i].first) { x_ = bounds[i].first; }
							while (!paste && bounds[i].first <= x_ && x_ < bounds[i].second)
							{
								if (entity.GetType() == "embedded")
								{
									if (x_ == bounds[i].first)
									{
										if (x_ + entity.GetWidth() <= bounds[i].second)
										{
											ExportImageCoords(entity);
											if (entity.GetHeight() > h_current_)
											{
												h_current_ = entity.GetHeight();
											}
											jump = false;
											x_ += entity.GetWidth();
											paste = true;
											if (x_ == bounds[i].second)
											{
												if (i == bounds.size() - 1)
												{
													jump = false;
													x_ = bounds[i].second;
												}
												else
												{
													jump = true;
													last_pasted_coords = make_pair(x_, y_);
													x_ = bounds[i + 1].first;
												}
											}
										}
										else
										{
											if (i == bounds.size() - 1)
											{
												jump = false;
												x_ = bounds[i].second;
											}
											else
											{
												jump = true;
												last_pasted_coords = make_pair(x_, y_);
												x_ = bounds[i + 1].first;
											}
										}
									}
									else
									{
										if (!prev_was_sur)
										{
											if (x_ + c_ + entity.GetWidth() <= bounds[i].second)
											{
												ExportImageCoords(Entity{ c_, 0, entity.GetWidth(), entity.GetHeight(), entity.GetType() });
												if (entity.GetHeight() > h_current_)
												{
													h_current_ = entity.GetHeight();
												}
												jump = false;
												x_ += (c_ + entity.GetWidth());
												paste = true;
											}
											else
											{
												if (i == bounds.size() - 1)
												{
													jump = false;
													x_ = bounds[i].second;
												}
												else
												{
													jump = true;
													last_pasted_coords = make_pair(x_, y_);
													x_ = bounds[i + 1].first;
												}
											}
										}
										else
										{
											if (x_ + entity.GetWidth() <= bounds[i].second)
											{
												ExportImageCoords(entity);
												if (entity.GetHeight() > h_current_)
												{
													h_current_ = entity.GetHeight();
												}
												jump = false;
												x_ += (entity.GetWidth());
												paste = true;
											}
											else
											{
												if (i == bounds.size() - 1)
												{
													jump = false;
													x_ = bounds[i].second;
												}
												else
												{
													jump = true;
													last_pasted_coords = make_pair(x_, y_);
													x_ = bounds[i + 1].first;
												}
											}
										}
									}
									prev_was_sur = false;
								}
								if (entity.GetType() == "surrounded")
								{
									if (x_ + entity.GetWidth() <= bounds[i].second)
									{
										ExportImageCoords(entity);
										surrounded_ys.insert(y_ + entity.GetHeight());
										SaveSurroundedImageData(entity);
										jump = false;
										x_ += entity.GetWidth();
										paste = true;
										if (x_ == bounds[i].second)
										{
											if (i == bounds.size() - 1)
											{
												jump = false;
												x_ = bounds[i].second;
											}
											else
											{
												jump = true;
												last_pasted_coords = make_pair(x_, y_);
												x_ = bounds[i + 1].first;
											}
										}
									}
									else
									{
										if (i == bounds.size() - 1)
										{
											jump = false;
											x_ = bounds[i].second;
										}
										else
										{
											jump = true;
											last_pasted_coords = make_pair(x_, y_);
											x_ = bounds[i + 1].first;
										}
									}
									prev_was_sur = true;
								}
							}
							if (paste)
							{
								break;
							}
						}
						if (!paste)
						{
							Newline();
							bounds = GetBoundaries();
						}
					}
					prev_was_floating = false;
				}
				else
				{
					int correct_x;
					int correct_y;
					if (jump)
					{
						correct_x = last_pasted_coords.first + entity.GetDx();
						correct_y = last_pasted_coords.second + entity.GetDy();
					}
					else
					{
						correct_x = x_ + entity.GetDx();
						correct_y = y_ + entity.GetDy();
					}
					if (prev_was_floating)
					{
						correct_x = floating_images[floating_images.size() - 1].first + entity.GetDx();
						correct_y = floating_images[floating_images.size() - 1].second + entity.GetDy();
					}
					if (correct_x < 0)
					{
						correct_x = 0;
					}
					if (correct_x + entity.GetWidth() > w_)
					{
						correct_x = w_ - entity.GetWidth();
					}
					floating_images.emplace_back(correct_x + entity.GetWidth(), correct_y);
					answer.emplace_back(correct_x, correct_y);
					prev_was_floating = true;
				}
			}
		}
	}
	void Newline() { x_ = 0; y_ += h_current_; h_current_ = h_; prev_was_sur = false; prev_was_floating = false; jump = false; }
	void SaveSurroundedImageData(const Entity& entity) { surrounded_images[x_] = make_pair(y_, entity); }
	void ExportImageCoords(const Entity& entity) { answer.emplace_back(x_ + entity.GetDx(), y_ + entity.GetDy()); }
	vector<pair<int, int>> GetBoundaries()
	{
		int lb = 0;
		vector<pair<int, int>> result;
		for (auto it = surrounded_images.begin(); it != surrounded_images.end(); it++)
		{
			int img_x = it->first;
			int img_y = it->second.first;
			auto obj = it->second.second;
			if (img_y + obj.GetHeight() > y_)
			{
				if (lb != img_x)
				{
					result.emplace_back(lb, img_x);
				}
				lb = img_x + obj.GetWidth();
			}
		}
		if (lb != w_)
		{
			result.emplace_back(lb, w_);
		}
		return result;
	}

private:
	int x_;// x pos
	int y_;// y pos
	int w_;// document width
	int h_;// string default height
	int h_current_;// current string height
	int c_;// char length
};

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	int w, h, c;
	(in >> w >> h >> c).get();

	Cursor cursor(0, 0, w, h, h, c);

	while (!in.eof())
	{
		vector<Entity> v;
		string line;
		string cur;
		getline(in, cur);
		while (!in.eof() && cur != "")
		{
			line += (' ' + cur + ' ');
			getline(in, cur);
		}
		if (in.eof())
		{
			line += (' ' + cur + ' ');
		}
		if (line.size() > 0)
		{
			string text;
			int i = 0;
			while (i < line.size())
			{
				char ch = line[i];
				if (ch == '(')
				{
					if (trim(text).size() > 0)
					{
						v.emplace_back(0, 0, text.size() * c, h, "text", text);
					}
					text = "";
					int dxx = 0;
					int dyy = 0;
					int ww, hh; string typee;
					while (ch != ')')
					{
						while (ch != '=')
						{
							ch = line[++i];
						}
						char mode = line[i - 1];
						char mmode = line[i - 2];
						if (mode == 'x')
						{
							dxx = ExtractValue(line, ch, i);
						}
						else if (mode == 'y')
						{
							dyy = ExtractValue(line, ch, i);
						}
						else if (mode == 'h')
						{
							ww = ExtractValue(line, ch, i);
						}
						else if (mode == 't' && mmode == 'h')
						{
							hh = ExtractValue(line, ch, i);
						}
						else
						{
							typee = ExtractString(line, ch, i);
						}
					}
					v.emplace_back(dxx, dyy, ww, hh, typee);
				}
				else
				{
					text += ch;
				}
				i++;
			}
			if (trim(text).size() > 0)
			{
				v.emplace_back(0, 0, text.size() * c, h, "text", text); //мейби просто переменную text сюда передать, не??? - подумаю)))
			}
			cursor.Paste(v);
		}
		if (cur.size() == 0)
		{
			cursor.Paste({});
		}
	}

	for (const auto& item : answer)
	{
		out << item.first << ' ' << item.second << '\n';
	}


	in.close();
	out.close();
	return 0;
}