/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:40:57 by nheo              #+#    #+#             */
/*   Updated: 2022/11/26 21:38:01 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

typedef struct s_pt
{
	double	x;
	double	y;
	double	z;
}	t_pt;

typedef struct s_ambient
{
	struct s_pt		color;
	double			ratio;
}	t_ambient;

/*
	struct s_pt	vp_ll; // 뷰포트 왼쪽 아래 꼭지점
	struct s_pt	hor; // 뷰포트 가로 방향 벡터
	struct s_pt	ver; // 뷰포트 세로 방향 벡터
	double		v_h; // 뷰포트 세로길이
	double		v_w; // 뷰포트 가로길이
*/
typedef struct s_cam
{
	struct s_pt	pos;
	struct s_pt	dir;
	struct s_pt	vp_ll;
	struct s_pt	hor;
	struct s_pt	ver;
	double		v_h;
	double		v_w;
	double		fov;
	double		focal_len;
}	t_cam;

typedef struct s_light
{
	struct s_pt	pos;
	double		ratio;
	struct s_pt	color;
}	t_light;

typedef struct s_sp
{
	struct s_pt		pos;
	struct s_pt		color;
	double			r;
}	t_sp;

typedef struct s_pl
{
	struct s_pt		pos;
	struct s_pt		dir;
	struct s_pt		color;
}	t_pl;

typedef struct s_cy
{
	struct s_pt		pos;
	struct s_pt		dir;
	struct s_pt		color;
	double			r;
	double			height;
}	t_cy;

/* t_list의 content 안에 들어갈 정보. content를 t_obj로 형변환해서 사용 */
typedef struct s_obj
{
	int				type;
	void			*obj_info;
}	t_obj;

/*
	object에 광선이 맞았는지 아닌지 체크하기 위한 정보
	t_pt		pos;	// 광선과 object가 만나는 지점
	t_pt		n_vec;	// 법선 벡터
	t_pt		albedo;	// object의 색깔
	double		t;		// 광선과 object가 만나는 지점까지의 거리
	double		t_min;	// 광선과 object가 만나는 지점까지의 최소 거리 (화면에 나타날 수 있는 최소 거리)
	double		t_max;	// 광선과 object가 만나는 지점까지의 최대 거리 (화면에 나타날 수 있는 최대 거리)
*/
typedef struct s_hit_check
{
	t_pt		pos;
	t_pt		n_vec;
	t_pt		albedo;
	double		t;
	double		t_min;
	double		t_max;
}	t_hit_check;

/* 추적할 광선에 대한 정보 */
typedef struct s_ray
{
	t_pt		pos;
	t_pt		dir;
}	t_ray;

/*
	t_pt		specular;	// 반사광
	t_pt		dif;	// 난반사
	double		spec;	// 입사각, 반사각 사이의 각도
	double		ks;		// 광택 정도
	double		ksn;	// 광택 계수 (높을수록 하이라이팅 범위 줄어든다)
*/
typedef struct s_pong
{
	t_pt		lig_dir;
	t_pt		view_dir;
	t_pt		ref_dir;
	t_pt		dif;
	t_pt		specular;
	double		spec;
	double		ks;
	double		ksn;
	double		kd;
	double		lig_len;
}	t_pong;

/*
	// mlx 관련 정보
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;		// 한 픽셀의 비트 수
	int					size_line;	// 한 행의 바이트 수
	int					endian;		// 뭔지 잘 모르겠음..
	// 오브젝트 관련 정보
	struct s_ambient	amb;		// 주변광
	struct s_cam		cam;		// 카메라
	struct s_light		light;		// 광원
	// event 관련 정보
	void				*clicked;		// 이동할 수 있도록 클릭된 오브젝트
	int					clicked_type;	// 클릭된 오브젝트의 타입
	t_list				*objs;
*/
typedef struct s_info
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
	struct s_ambient	amb;
	struct s_cam		cam;
	struct s_light		light;
	void				*clicked;
	int					clicked_type;
	t_list				*objs;
}	t_info;

#endif
